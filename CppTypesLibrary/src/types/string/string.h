#pragma once

#include <Windows.h>
#include <psapi.h>
#include <libloaderapi.h>
#include <iostream>

#define _STRING_SSO_ALIGNMENT 32

constexpr const char* _emptyString = "";

/* A constexpr, sso, and const segment enabled string class. Can check if const char*'s passed in exist within the application const data segment,
and avoid doing unnecessary copying with this.
@param BUFFER_SIZE: Size of the sso character buffer. Must be a multiple of 32. */
template<size_t BUFFER_SIZE = 32>
struct
#ifdef _MSC_VER
	__declspec(align(_STRING_SSO_ALIGNMENT))
#else
	alignas(_STRING_SSO_ALIGNMENT)
#endif
	buffer_string
{
	static_assert(BUFFER_SIZE % _SSO_ALIGNMENT == 0, "The size of the buffer characters must be a multiple of _STRING_SSO_ALIGNMENT (32)");

private:

	/* Small String Optimization buffer. */
	char sso[BUFFER_SIZE];

	/* Length of the string, whether in the buffer or the heap data. */
	size_t length;

	/* Heap data or constexpr string. */
	char* data;

	/* Capacity of the heap data string. */
	size_t capacity;

	/* Is this string currently using the sso buffer? */
	unsigned char flagSSOBuffer : 1;

	/* Is this string's data pointer held within the const segment? */
	unsigned char flagConstSegment : 1;

private:

	constexpr static size_t GetMaxSSOLength() {
		return BUFFER_SIZE - 1;
	}

	/* Sets the data pointer to a const segment. Assumes the pointer passed in is within the const segment. */
	constexpr void SetStringToConstSegment(const char* segment) {
		data = (char*)segment;
		flagSSOBuffer = false;
		flagConstSegment = true;
	}

	/* Yeah :) */
	constexpr void SetLength(size_t newLength) {
		length = newLength;
	}

	/* Sets the sso buffer to a copy of whatever the characters in chars are.
	Uses len + 1 to include null terminator. Sets the relevant flags. */
	constexpr void SetSSOBufferChars(const char* chars, size_t len) {
		flagSSOBuffer = true;
		flagConstSegment = false;
		CopyCharsIntoBuffer(chars, len);
		sso[BUFFER_SIZE - 1] = '\0';
	}

	/* Sets the data pointer to new chars by copying them. Assumes passed in chars is not within the const segment.
	Uses len + 1 to include null terminator. Sets the relevant flags.*/
	constexpr void SetDataChars(const char* chars, size_t len) {
		flagSSOBuffer = false;
		flagConstSegment = false;
		CopyCharsIntoData(chars, len);
	}

	/* Copies numToCopy + 1, primarily being the null terminator. */
	constexpr void CopyCharsIntoBuffer(const char* chars, size_t numToCopy) {
		std::copy(chars, &chars[numToCopy + 1], sso);
	}

	/* Copies numToCopy + 1, primarily being the null terminator. */
	constexpr void CopyCharsIntoData(const char* chars, size_t numToCopy) {
		std::copy(chars, &chars[numToCopy + 1], data);
	}

	/* Attempts to delete the data string. Will not delete under the following conditions.
	1. The string is using the SSO buffer.
	2. The data pointer is nullptr.
	3. If the data pointer is in the const segment and not constexpr. */
	constexpr void TryDeleteDataString() {
		if (!flagSSOBuffer && data != nullptr && data != _emptyString) {
			if (!std::is_constant_evaluated() && flagConstSegment) {
				delete[] data;
				return;
			}
			delete[] data;
		}
	}

	/* Performs necessary construction for this string's values from a const char*. */
	inline constexpr void ConstructConstChar(const char* str)
	{
		const size_t len = StrLen(str);
		SetLength(len);
		if (!std::is_constant_evaluated() && buffer_string::IsConstCharInConstSegment(str)) {
			SetStringToConstSegment(str);
			return;
		}

		if (len > GetMaxSSOLength()) {
			capacity = len + 1;
			data = new char[capacity];
			SetDataChars(str, len);
		}
		else {
			SetSSOBufferChars(str, len);
		}
	}

	/* Performs necessary construction for this string's values from another string through copying. */
	inline constexpr void ConstructCopy(const buffer_string<BUFFER_SIZE>& other)
	{
		const size_t len = other.Len();
		const char* str = other.CStr();
		SetLength(len);
		if (!std::is_constant_evaluated() && buffer_string::IsConstCharInConstSegment(str)) {
			SetStringToConstSegment(str);
			return;
		}

		if (len > GetMaxSSOLength()) {
			capacity = len + 1;
			data = new char[capacity];
			SetDataChars(str, len);
		}
		else {
			SetSSOBufferChars(str, len);
		}
	}

	/* Performs necessary construction for this string's values from moving another string. Sets the other string data to by nullptr if it's using it. */
	inline constexpr void ConstructMove(buffer_string<BUFFER_SIZE>&& other) noexcept
	{
		const size_t len = other.Len();
		const char* str = other.CStr();
		SetLength(len);

		if (!std::is_constant_evaluated() && buffer_string::IsConstCharInConstSegment(str)) {
			data = (char*)str;
			flagSSOBuffer = false;
			capacity = 0;
			flagConstSegment = true;
			return;
		}

		if (len > GetMaxSSOLength()) {
			capacity = len + 1;
			data = (char*)str;
			other.data = nullptr;
			flagSSOBuffer = false;

		}
		else {
			SetSSOBufferChars(str, len);
		}
	}

public:

	/* Get if a const char* is within the runtime const segment of the running application. Not constexpr valid. Currently only works on windows. */
	[[nodiscard]] static bool IsConstCharInConstSegment(const char* str)
	{
#ifdef _MSC_VER
		static MODULEINFO moduleInfo;
		static const bool b = GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(NULL), &moduleInfo, sizeof(MODULEINFO));
		static const uintptr_t entryPoint = uintptr_t(moduleInfo.EntryPoint);
		static const uintptr_t endPoint = uintptr_t(moduleInfo.EntryPoint) + uintptr_t(moduleInfo.SizeOfImage);
		return uintptr_t(str) > entryPoint && uintptr_t(str) < endPoint;
#else
		return false;
#endif
	}

	/* Check the length of a const char*
	TODO SIMD / SSE / AVX optimizations. */
	[[nodiscard]] constexpr static size_t StrLen(const char* str) {
		return std::char_traits<char>::length(str);
	}

	/* Check if two character arrays are equal.
	TODO SIMD / SSE / AVX optimizations. */
	[[nodiscard]] constexpr static bool StrEqual(const char* str1, const char* str2, size_t num) {
		for (int i = 0; i < num; i++) {
			if (str1[i] != str2[i]) {
				return false;
			}
		}
		return true;
	}

	/**/
	constexpr buffer_string()
		: sso{ '\0' }, length{ 0 }, capacity{ 0 }
	{
		SetStringToConstSegment(_emptyString);
	}

	/**/
	constexpr buffer_string(const char* str)
		: sso{ '\0' }, data{ nullptr }, length{ 0 }, capacity{ 0 }
	{
		ConstructConstChar(str);
	}

	/**/
	constexpr buffer_string(const buffer_string<BUFFER_SIZE>& other)
		: sso{ '\0' }, data{ nullptr }, length{ 0 }, capacity{ 0 }
	{
		ConstructCopy(other);
	}

	/**/
	constexpr buffer_string(buffer_string<BUFFER_SIZE>&& other) noexcept
		: sso{ '\0' }, data{ nullptr }, length{ 0 }, capacity{ 0 }
	{
		ConstructMove(std::move(other));
	}

	/**/
	constexpr ~buffer_string()
	{
		TryDeleteDataString();
	}

	/**/
	constexpr buffer_string<BUFFER_SIZE>& operator = (const char* str)
	{
		TryDeleteDataString();
		ConstructConstChar(str);
		return *this;
	}

	/**/
	constexpr buffer_string<BUFFER_SIZE>& operator = (const buffer_string<BUFFER_SIZE>& other)
	{
		TryDeleteDataString();
		ConstructCopy(other);
		return *this;
	}

	/**/
	constexpr buffer_string<BUFFER_SIZE>& operator = (buffer_string<BUFFER_SIZE>&& other) noexcept
	{
		TryDeleteDataString();
		ConstructMove(std::move(other));
		return *this;
	}

	/* Whether this string is currently using the sso buffer. */
	[[nodiscard]] constexpr bool IsSSO() const { return flagSSOBuffer; }

	/* Whether this string is currently pointing to data in the const data segment. */
	[[nodiscard]] constexpr bool IsConstSegment() const { return flagConstSegment; }

	/* Get the length of this string. */
	[[nodiscard]] constexpr size_t Len() const { return length; }

	/* Get the const char* string version of this string. Pulls either the sso buffer or the data pointer. */
	[[nodiscard]] constexpr const char* CStr() const {
		if (!flagSSOBuffer) {
			return data;
		}
		return sso;
	}

	/**/
	[[nodiscard]] constexpr bool IsEmpty() const { Len() == 0; }

	/* Get a character at a specified index. Not a reference to the character though. */
	[[nodiscard]] constexpr char At(size_t index) {
		return CStr()[index];
	}

	/* Get a character at a specified index. Not a reference to the character though. */
	[[nodiscard]] constexpr char operator[](size_t index) {
		return At(index);
	}

	/* Check if this string is equal to a const char*. Can check if they are within the const data segment and bypass most string checks. */
	[[nodiscard]] constexpr bool operator == (const char* str) const
	{
		if (!std::is_constant_evaluated() && buffer_string::IsConstCharInConstSegment(str) && flagConstSegment) {
			if (data == str) {
				return true;
			}
		}
		const size_t len = StrLen(str);
		if (Len() != len) {
			return false;
		}
		return StrEqual(CStr(), str, len);
	}

	/* Check if this string is equal to another string. Can check if they both use the same const data segment pointer and bypass most string checks. */
	[[nodiscard]] constexpr bool operator == (const buffer_string<BUFFER_SIZE>& other) const
	{
		if (!std::is_constant_evaluated() && flagConstSegment && other.flagConstSegment) {
			if (data == other.data) {
				return true;
			}
		}
		const size_t len = other.Len();
		if (Len() != len) {
			return false;
		}
		return StrEqual(CStr(), other.CStr(), len);
	}

	/* std::cout << string */
	friend std::ostream& operator << (std::ostream& os, const buffer_string<BUFFER_SIZE>& _string) {
		return os << _string.CStr();
	}

};

/* A constexpr, sso, and const segment enabled string class. Can check if const char*'s passed in exist within the application const data segment,
and avoid doing unnecessary copying with this. Has an internal sso buffer size of 32. */
typedef buffer_string<32> string;
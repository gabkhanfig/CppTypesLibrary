#pragma once

#include <iomanip>
#include <iostream>



constexpr size_t maxSSOLength = 23;
constexpr size_t STRING_SSO_FLAG_BIT = 1ULL << 63;

/* Constexpr and SSO enabled string. Can store strings of length 23 within sso buffer (excluding null terminator). */
struct string 
{
public:

	struct LongString {
		char* data;
		size_t capacity;
		size_t padding;

		constexpr LongString()
			: data(nullptr), capacity(0), padding(0)
		{}
	};

	struct SmallString {
		char chars[maxSSOLength + 1];

		constexpr SmallString() 
			: chars{'\0' }
		{}

		constexpr void operator = (const LongString& other) {
			chars[0] = '\0';
		}
	};

	union StringRep {
		SmallString sso;
		LongString lng;

		constexpr StringRep() {
			lng = LongString();
		}
	};

private:

	size_t flag : 1;
	size_t length : 63;
	StringRep rep;

	constexpr void SetFlagSmall() {
		flag = false;
	}

	constexpr void SetFlagLong() {
		flag = true;
	}

	constexpr void SetLength(size_t newLength) {
		length = newLength;
	}

	/* Deletes the long string representation data buffer if the string is a long string, and the data buffer is non-null. */
	constexpr void DeleteDataBuffer() {
		if (IsLong()) {
			if (rep.lng.data) {
				delete[] rep.lng.data;
			}
		}
	}


public:

	constexpr bool IsLong() const {
		return flag;
	}

	constexpr size_t Length() const {
		return length;
	}

	constexpr size_t Capacity() const {
		return rep.lng.capacity;
	}

	constexpr string() {
		rep.sso.chars[0] = '\0';
		SetLength(0);
		SetFlagSmall();
	}

	constexpr string(const char* str) {
		const size_t len = std::char_traits<char>::length(str);
		const size_t cap = len + 1;
		const bool isLongStr = len > maxSSOLength;
		SetLength(len);
		if (isLongStr) {
			SetFlagLong();
			rep.lng.capacity = cap;
			rep.lng.data = new char[cap];
			std::copy(str, &str[cap], rep.lng.data);
		}
		else {
			SetFlagSmall();
			rep.sso = SmallString();
			std::copy(str, &str[cap], rep.sso.chars);
		}
	}

	constexpr string(string&& other) noexcept {
		SetLength(other.Length());
		if (other.IsLong()) {
			SetFlagLong();
			rep.lng.data = other.rep.lng.data;
			other.rep.lng.data = nullptr;
			rep.lng.capacity = other.rep.lng.capacity;
		}
		else {
			SetFlagSmall();
			rep.sso = SmallString();
			std::copy(other.rep.sso.chars, &other.rep.sso.chars[maxSSOLength + 1], rep.sso.chars);
		}
	}

	constexpr string(const string& other) {
		const char* str = other.CStr();
		SetLength(other.Length());
		if (other.IsLong()) {
			SetFlagLong();
			rep.lng.capacity = other.rep.lng.capacity;
			rep.lng.data = new char[Length() + 1];
			std::copy(str, &str[Length() + 1], rep.lng.data);
		}
		else {
			SetFlagSmall();
			rep.sso = SmallString();
			std::copy(other.rep.sso.chars, &other.rep.sso.chars[maxSSOLength + 1], rep.sso.chars);
		}
	}

	constexpr ~string() {
		DeleteDataBuffer();
	}

	constexpr const char* CStr() const {
		if (IsLong()) {
			return rep.lng.data;
		}
		else {
			return rep.sso.chars;
		}
	}

	constexpr void operator = (const char* str) {
		DeleteDataBuffer();
		const size_t len = std::char_traits<char>::length(str);
		const size_t cap = len + 1;
		const bool isLongStr = len > maxSSOLength;
		SetLength(len);
		if (isLongStr) {
			SetFlagLong();
			rep.lng.capacity = cap;
			rep.lng.data = new char[cap];
			std::copy(str, &str[cap], rep.lng.data);
		}
		else {
			SetFlagSmall();
			rep.sso = SmallString();
			std::copy(str, &str[cap], rep.sso.chars);
		}
	}

	constexpr void operator = (string&& other) noexcept {
		DeleteDataBuffer();
		SetLength(other.Length());
		if (other.IsLong()) {
			SetFlagLong();
			rep.lng.data = other.rep.lng.data;
			other.rep.lng.data = nullptr;
			rep.lng.capacity = other.rep.lng.capacity;
		}
		else {
			SetFlagSmall();
			rep.sso = SmallString();
			std::copy(other.rep.sso.chars, &other.rep.sso.chars[maxSSOLength + 1], rep.sso.chars);
		}
	}

	constexpr void operator = (const string& other) {
		DeleteDataBuffer();
		const char* str = other.CStr();
		SetLength(other.Length());
		if (other.IsLong()) {
			SetFlagLong();
			rep.lng.capacity = other.rep.lng.capacity;
			rep.lng.data = new char[Length() + 1];
			std::copy(str, &str[Length() + 1], rep.lng.data);
		}
		else {
			SetFlagSmall();
			rep.sso = SmallString();
			std::copy(other.rep.sso.chars, &other.rep.sso.chars[maxSSOLength + 1], rep.sso.chars);
		}
	}


	
};
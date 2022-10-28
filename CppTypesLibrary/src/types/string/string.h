#pragma once

#include <iomanip>

/* Constexpr and SSO enabled string. Can store strings of length 23 within sso buffer (excluding null terminator). */
struct string
{
public:

	static constexpr size_t maxSSOLength = 23;

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
			: chars{ '\0' }
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

	/* Flag bit representing whether the string is in the long string representation or not. */
	size_t flag : 1;

	/* Length of contained string, sso or not. */
	size_t length : 63;

	/**/
	StringRep rep;

	/**/
	constexpr void SetFlagSmall() {
		flag = false;
	}

	/**/
	constexpr void SetFlagLong() {
		flag = true;
	}

	/**/
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

	/**/
	constexpr bool IsLong() const {
		return flag;
	}

	/**/
	constexpr size_t Length() const {
		return length;
	}

	/**/
	constexpr size_t Capacity() const {
		return rep.lng.capacity;
	}

	/**/
	constexpr string() {
		rep.sso.chars[0] = '\0';
		SetLength(0);
		SetFlagSmall();
	}

	/**/
	constexpr string(const char* str) {
		if (str == nullptr) {
			rep.sso.chars[0] = '\0';
			SetLength(0);
			SetFlagSmall();
			return;
		}

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

	/**/
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

	/**/
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
	
	/**/
	constexpr ~string() {
		DeleteDataBuffer();
	}

	/**/
	constexpr const char* CStr() const {
		if (IsLong()) {
			return rep.lng.data;
		}
		else {
			return rep.sso.chars;
		}
	}

	/**/
	constexpr void operator = (const char* str) {
		DeleteDataBuffer();

		if (str == nullptr) {
			rep.sso.chars[0] = '\0';
			SetLength(0);
			SetFlagSmall();
			return;
		}

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

	/**/
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

	/**/
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

	/**/
	constexpr char At(size_t index) {
		if (index > length + 1) {
			return '\0';
		}
		return CStr()[index];
	}

	/**/
	constexpr char operator[] (size_t index) {
		return At(index);
	}

	/**/
	constexpr bool Contains(char character) {
		const char* cstr = CStr();
		for (size_t i = 0; i < Length(); i++) {
			if (cstr[i] == character) return true;
		}
		return false;
	}

	/**/
	constexpr bool Contains(const char* str) {
		const size_t len = std::char_traits<char>::length(str);

		if (len > Length() || len == 0) {
			return false;
		}

		const char* cstr = CStr();

		for (size_t i = 0; i < Length(); i++) {
			if (cstr[i] != str[0]) continue;
			if (std::is_constant_evaluated()) {
				bool isEqual = true;
				for (size_t j = 0; j < len; j++) {
					if (cstr[i + j] != str[j]) {
						isEqual = false;
						break;
					}
				}
				if (isEqual) {
					return true;
				}
			}

			/* The non-constexpr branch does not have test coverage. */
			else {
				if ((i + len) > Length()) return false;
				if (memcmp(&cstr[i], str, len) == 0) {
					return true;
				}
			}
		}
		return false;
	}

	/**/
	constexpr bool Contains(const string& other) {
		const size_t len = other.Length();

		if (len > Length() || len == 0) {
			return false;
		}

		const char* cstr = CStr();
		const char* otherstr = other.CStr();

		for (size_t i = 0; i < Length(); i++) {
			if (cstr[i] != otherstr[0]) continue;
			if (std::is_constant_evaluated()) {
				bool isEqual = true;
				for (size_t j = 0; j < len; j++) {
					if (cstr[i + j] != otherstr[j]) {
						isEqual = false;
						break;
					}
				}
				if (isEqual) {
					return true;
				}
			}

			/* The non-constexpr branch does not have test coverage. */
			else {
				if ((i + len) > Length()) return false;
				if (memcmp(&cstr[i], otherstr, len) == 0) {
					return true;
				}
			}
		}
		return false;
	}

	/* Make substring from startIndex (inclusive) and endIndex (exclusive). */
	constexpr string Substring(size_t startIndex, size_t endIndex) {
		if (startIndex > Length() || endIndex > Length() || startIndex > endIndex) return string();

		const size_t len = endIndex - startIndex;
		const size_t cap = len + 1;
		const char* startBuffer = &CStr()[startIndex];
		const char* endBuffer = &CStr()[endIndex];

		string s;
		s.length = len;
		if (len > maxSSOLength) {
			s.SetFlagLong();
			s.rep.lng.capacity = cap;
			s.rep.lng.data = new char[cap];
			std::copy(startBuffer, endBuffer, s.rep.lng.data);
			s.rep.lng.data[len] = '\0';
		}
		else {
			s.SetFlagSmall();
			s.rep.sso = SmallString();
			std::copy(startBuffer, endBuffer, s.rep.sso.chars);
			s.rep.sso.chars[len] = '\0';
		}
		return s;
	}

	constexpr bool operator == (const char* str) {
		if (str == nullptr) return false;
		const size_t len = std::char_traits<char>::length(str);
		if (len != Length()) return false;

		const char* cstr = CStr();

		// Assume both are null terminated.
		for (size_t i = 0; i < Length(); i++) {
			if (cstr[i] != str[i]) return false;
		}
		return true;
	}

	constexpr bool operator == (const string& other) {
		if (other.Length() != Length()) return false;

		const char* str = other.CStr();
		const char* cstr = CStr();

		// Assume both are null terminated.
		for (size_t i = 0; i < Length(); i++) {
			if (cstr[i] != str[i]) return false;
		}
		return true;
	}



	
};
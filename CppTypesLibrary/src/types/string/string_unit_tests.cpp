#include "string.h"

#define TEST_TYPES "String"
#include <testframework/unit_test_compile_time.h>

namespace StringUnitTests
{
	constexpr bool DefaultConstructIsSmall() {
		string s;
		return !s.IsLong();
	}
	TEST_ASSERT(DefaultConstructIsSmall(), "Default constructed string is not sso enabled");

	constexpr bool DefaultConstructNullTerminator() {
		string s;
		return s.CStr()[0] == '\0';
	}
	TEST_ASSERT(DefaultConstructNullTerminator(), "Default constructed string does not have null terminator as first character");

	constexpr bool DefaultConstructLength() {
		string s;
		return s.Length() == 0;
	}
	TEST_ASSERT(DefaultConstructLength(), "Default constructed string does not have a length of 0");

	constexpr bool ConstCharConstructSmallIsSmall() {
		string s = "a";
		return !s.IsLong();
	}
	TEST_ASSERT(ConstCharConstructSmallIsSmall(), "Small const char* constructed string is not sso enabled");

	constexpr bool ConstCharConstructSmallChars() {
		string s = "a";
		const bool firstChar = s.CStr()[0] == 'a';
		const bool secondChar = s.CStr()[1] == '\0';
		return firstChar && secondChar;
	}
	TEST_ASSERT(ConstCharConstructSmallChars(), "Small const char* constructed string has incorrect chararacters");

	constexpr bool ConstCharConstructSmallLength() {
		string s = "a";
		return s.Length() == 1;
	}
	TEST_ASSERT(ConstCharConstructSmallLength(), "Small const char* constructed string has an invalid length");

	constexpr bool ConstCharConstructLongIsLong() {
		string s = "abcdefghijklmnopqrstuvwxyz";
		return s.IsLong();
	}
	TEST_ASSERT(ConstCharConstructLongIsLong(), "Long const char* constructed string is not sso disabled");

	constexpr bool ConstCharConstructLongChars() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		const char* cstr = s.CStr();
		for (int i = 0; i < 26; i++) {
			if (cstr[i] != alphabet[i]) return false;
		}
		if (cstr[26] != '\0') return false;
		return true;
	}
	TEST_ASSERT(ConstCharConstructLongChars(), "Long const char* constructed string has incorrect characters");

	constexpr bool ConstCharConstructLongLength() {
		string s = "abcdefghijklmnopqrstuvwxyz";
		return s.Length() == 26;
	}
	TEST_ASSERT(ConstCharConstructLongLength(), "Long const char* constructed string has an invalid length");

	constexpr bool MoveConstructSmallIsSmall() {
		string s = "a";
		string s2 = std::move(s);
		return !s2.IsLong();
	}
	TEST_ASSERT(MoveConstructSmallIsSmall(), "Small move constructed string is not sso enabled");

	constexpr bool MoveConstructSmallChars() {
		string s = "a";
		string s2 = std::move(s);
		const bool firstChar = s2.CStr()[0] == 'a';
		const bool secondChar = s2.CStr()[1] == '\0';
		return firstChar && secondChar;
	}
	TEST_ASSERT(MoveConstructSmallChars(), "Small move constructed string has incorrect characters");

	constexpr bool MoveConstructSmallLength() {
		string s = "a";
		string s2 = std::move(s);
		return s2.Length() == 1;
	}
	TEST_ASSERT(MoveConstructSmallLength(), "Small move constructed string has an invalid length");

	constexpr bool MoveConstructLongIsLong() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		string s2 = std::move(s);
		return s2.IsLong();
	}
	TEST_ASSERT(MoveConstructLongIsLong(), "Long move constructed string is not sso disabled");

	constexpr bool MoveConstructLongChars() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		string s2 = std::move(s);
		const char* cstr = s2.CStr();
		for (int i = 0; i < 26; i++) {
			if (cstr[i] != alphabet[i]) return false;
		}
		if (cstr[26] != '\0') return false;
		return true;
	}
	TEST_ASSERT(MoveConstructLongChars(), "Long move constructed string has incorrect characters");


	constexpr bool MoveConstructLongLength() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		string s2 = std::move(s);
		return s2.Length() == 26;
	}
	TEST_ASSERT(MoveConstructLongLength(), "Long move constructed string has an invalid length");

	constexpr bool MoveConstructLongInvalidateOther() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		string s2 = std::move(s);
		return s.CStr() == nullptr;
	}
	TEST_ASSERT(MoveConstructLongInvalidateOther(), "Long string after move was not invalidated");
}
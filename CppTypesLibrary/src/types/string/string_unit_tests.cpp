#include "string.h"

#define TEST_TYPES "String"
#include <testframework/unit_test_compile_time.h>

namespace StringUnitTests
{

#pragma region Default_Constructor

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

#pragma endregion

#pragma region Const_Char*_Constructor

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

#pragma endregion

#pragma region Move_Constructor

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

#pragma endregion

#pragma region Copy_Constructor

	constexpr bool CopyConstructSmallIsSmall() {
		string s = "a";
		string s2 = s;
		return !s2.IsLong();
	}
	TEST_ASSERT(CopyConstructSmallIsSmall(), "Small copy constructed string is not sso enabled");

	constexpr bool CopyConstructSmallChars() {
		string s = "a";
		string s2 = s;
		const bool firstChar = s2.CStr()[0] == 'a';
		const bool secondChar = s2.CStr()[1] == '\0';
		return firstChar && secondChar;
	}
	TEST_ASSERT(CopyConstructSmallChars(), "Small copy constructed string has incorrect characters");

	constexpr bool CopyConstructSmallLength() {
		string s = "a";
		string s2 = s;
		return s2.Length() == 1;
	}
	TEST_ASSERT(CopyConstructSmallLength(), "Small copy constructed string has an invalid length");

	constexpr bool CopyConstructLongIsLong() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		string s2 = s;
		return s2.IsLong();
	}
	TEST_ASSERT(CopyConstructLongIsLong(), "Long copy constructed string is not sso disabled");

	constexpr bool CopyConstructLongChars() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		string s2 = s;
		const char* cstr = s2.CStr();
		for (int i = 0; i < 26; i++) {
			if (cstr[i] != alphabet[i]) return false;
		}
		if (cstr[26] != '\0') return false;
		return true;
	}
	TEST_ASSERT(CopyConstructLongChars(), "Long copy constructed string has incorrect characters");

	constexpr bool CopyConstructLongLength() {
		const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
		string s = alphabet;
		string s2 = s;
		return s2.Length() == 26;
	}
	TEST_ASSERT(CopyConstructLongLength(), "Long copy constructed string has an invalid length");

#pragma endregion

#pragma region Const_Char*_Assignment_Operator_=

	constexpr bool AssignmentConstCharSmallToSmallIsSmall() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = smallstr;
		s = otherSmall;
		return !s.IsLong();
	}
	TEST_ASSERT(AssignmentConstCharSmallToSmallIsSmall(), "Small to small assignment string is not small");

	constexpr bool AssignmentConstCharLongToLongIsLong() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = longstr;
		s = otherLong;
		return s.IsLong();
	}
	TEST_ASSERT(AssignmentConstCharLongToLongIsLong(), "Long to long assignment string is not long");

	constexpr bool AssignmentConstCharSmallToLongIsLong() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		s = longstr;
		return s.IsLong();
	}
	TEST_ASSERT(AssignmentConstCharSmallToLongIsLong(), "Small to long assignment string is not long");

	constexpr bool AssignmentConstCharLongToSmallIsSmall() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		s = smallstr;
		return !s.IsLong();
	}
	TEST_ASSERT(AssignmentConstCharLongToSmallIsSmall(), "Long to small assignment string is not small");

	constexpr bool AssignmentConstCharSmallToSmallChars() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = smallstr;
		s = otherSmall;
		const char* cstr = s.CStr();
		for (int i = 0; i < 8; i++) {
			if (cstr[i] != otherSmall[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentConstCharSmallToSmallChars(), "Small to small assignment string has incorrect characters");

	constexpr bool AssignmentConstCharLongToLongChars() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = longstr;
		s = otherLong;
		const char* cstr = s.CStr();
		for (int i = 0; i < 51; i++) {
			if (cstr[i] != otherLong[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentConstCharLongToLongChars(), "Long to long assignment string has incorrect characters");

	constexpr bool AssignmentConstCharSmallToLongChars() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		s = longstr;
		const char* cstr = s.CStr();
		for (int i = 0; i < 27; i++) {
			if (cstr[i] != longstr[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentConstCharSmallToLongChars(), "Small to long assignment string has incorrect characters");

	constexpr bool AssignmentConstCharLongToSmallChars() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		s = smallstr;
		const char* cstr = s.CStr();
		for (int i = 0; i < 2; i++) {
			if (cstr[i] != smallstr[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentConstCharLongToSmallChars(), "Long to small assignment string has incorrect characters");

	constexpr bool AssignmentConstCharSmallToSmallLength() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = smallstr;
		s = otherSmall;
		return s.Length() == 7;
	}
	TEST_ASSERT(AssignmentConstCharSmallToSmallLength(), "Small to small assignment string has an invalid length");

	constexpr bool AssignmentConstCharLongToLongLength() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = longstr;
		s = otherLong;
		return s.Length() == 50;
	}
	TEST_ASSERT(AssignmentConstCharLongToLongLength(), "Long to long assignment string has an invalid length");

	constexpr bool AssignmentConstCharSmallToLongLength() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		s = longstr;
		return s.Length() == 26;
	}
	TEST_ASSERT(AssignmentConstCharSmallToLongLength(), "Small to long assignment string has an invalid length");

	constexpr bool AssignmentConstCharLongToSmallLength() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		s = smallstr;
		return s.Length() == 1;
	}
	TEST_ASSERT(AssignmentConstCharLongToSmallLength(), "Long to small assignment string has an invalid length");

#pragma endregion

#pragma region Move_Assignment_Operator_=

	constexpr bool AssignmentMoveSmallToSmallIsSmall() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = otherSmall;
		string s2 = smallstr;
		s2 = std::move(s);
		return !s2.IsLong();
	}
	TEST_ASSERT(AssignmentMoveSmallToSmallIsSmall(), "Small to small move assignment string is not small");

	constexpr bool AssignmentMoveLongToLongIsLong() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = otherLong;
		string s2 = longstr;
		s2 = std::move(s);
		return s2.IsLong();
	}
	TEST_ASSERT(AssignmentMoveLongToLongIsLong(), "Long to long move assignment string is not long");

	constexpr bool AssignmentMoveSmallToLongIsLong() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		string s2 = smallstr;
		s2 = std::move(s);
		return s2.IsLong();
	}
	TEST_ASSERT(AssignmentMoveSmallToLongIsLong(), "Small to long move assignment string is not long");

	constexpr bool AssignmentMoveLongToSmallIsSmall() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		string s2 = longstr;
		s2 = std::move(s);
		return !s2.IsLong();
	}
	TEST_ASSERT(AssignmentMoveLongToSmallIsSmall(), "Long to small move assignment string is not small");

	constexpr bool AssignmentMoveSmallToSmallChars() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = otherSmall;
		string s2 = smallstr;
		s2 = std::move(s);
		const char* cstr = s2.CStr();
		for (int i = 0; i < 8; i++) {
			if (cstr[i] != otherSmall[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentMoveSmallToSmallChars(), "Small to small move assignment string has incorrect characters");

	constexpr bool AssignmentMoveLongToLongChars() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = otherLong;
		string s2 = longstr;
		s2 = std::move(s);
		const char* cstr = s2.CStr();
		for (int i = 0; i < 51; i++) {
			if (cstr[i] != otherLong[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentMoveLongToLongChars(), "Long to long move assignment string has incorrect characters");

	constexpr bool AssignmentMoveSmallToLongChars() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		string s2 = smallstr;
		s2 = std::move(s);
		const char* cstr = s2.CStr();
		for (int i = 0; i < 27; i++) {
			if (cstr[i] != longstr[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentMoveSmallToLongChars(), "Small to long move assignment string has incorrect characters");

	constexpr bool AssignmentMoveLongToSmallChars() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		string s2 = longstr;
		s2 = std::move(s);
		const char* cstr = s2.CStr();
		for (int i = 0; i < 2; i++) {
			if (cstr[i] != smallstr[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentMoveLongToSmallChars(), "Long to small move assignment string has incorrect characters");

	constexpr bool AssignmentMoveSmallToSmallLength() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = otherSmall;
		string s2 = smallstr;
		s2 = std::move(s);
		return s2.Length() == 7;
	}
	TEST_ASSERT(AssignmentMoveSmallToSmallLength(), "Small to small move assignment string has an invalid length");

	constexpr bool AssignmentMoveLongToLongLength() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = otherLong;
		string s2 = longstr;
		s2 = std::move(s);
		return s2.Length() == 50;
	}
	TEST_ASSERT(AssignmentMoveLongToLongLength(), "Long to long move assignment string has an invalid length");

	constexpr bool AssignmentMoveSmallToLongLength() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		string s2 = smallstr;
		s2 = std::move(s);
		return s2.Length() == 26;
	}
	TEST_ASSERT(AssignmentMoveSmallToLongLength(), "Small to long move assignment string has an invalid length");

	constexpr bool AssignmentMoveLongToSmallLength() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		string s2 = longstr;
		s2 = std::move(s);
		return s2.Length() == 1;
	}
	TEST_ASSERT(AssignmentMoveLongToSmallLength(), "Long to small move assignment string has an invalid length");

	constexpr bool AssignmentMoveLongInvalidateOther() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = otherLong;
		string s2 = longstr;
		s2 = std::move(s);
		return s.CStr() == nullptr;
	}
	TEST_ASSERT(AssignmentMoveLongInvalidateOther(), "Long string after assignment move was not invalidated");

#pragma endregion

#pragma region Copy_Assignment_Operator_=

	constexpr bool AssignmentCopySmallToSmallIsSmall() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = otherSmall;
		string s2 = smallstr;
		s2 = s;
		return !s2.IsLong();
	}
	TEST_ASSERT(AssignmentCopySmallToSmallIsSmall(), "Small to small copy assignment string is not small");

	constexpr bool AssignmentCopyLongToLongIsLong() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = otherLong;
		string s2 = longstr;
		s2 = s;
		return s2.IsLong();
	}
	TEST_ASSERT(AssignmentCopyLongToLongIsLong(), "Long to long copy assignment string is not long");

	constexpr bool AssignmentCopySmallToLongIsLong() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		string s2 = smallstr;
		s2 = s;
		return s2.IsLong();
	}
	TEST_ASSERT(AssignmentCopySmallToLongIsLong(), "Small to long copy assignment string is not long");

	constexpr bool AssignmentCopyLongToSmallIsSmall() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		string s2 = longstr;
		s2 = s;
		return !s2.IsLong();
	}
	TEST_ASSERT(AssignmentCopyLongToSmallIsSmall(), "Long to small copy assignment string is not small");

	constexpr bool AssignmentCopySmallToSmallChars() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = otherSmall;
		string s2 = smallstr;
		s2 = s;
		const char* cstr = s2.CStr();
		for (int i = 0; i < 8; i++) {
			if (cstr[i] != otherSmall[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentCopySmallToSmallChars(), "Small to small copy assignment string has incorrect characters");

	constexpr bool AssignmentCopyLongToLongChars() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = otherLong;
		string s2 = longstr;
		s2 = s;
		const char* cstr = s2.CStr();
		for (int i = 0; i < 51; i++) {
			if (cstr[i] != otherLong[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentCopyLongToLongChars(), "Long to long copy assignment string has incorrect characters");

	constexpr bool AssignmentCopySmallToLongChars() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		string s2 = smallstr;
		s2 = s;
		const char* cstr = s2.CStr();
		for (int i = 0; i < 27; i++) {
			if (cstr[i] != longstr[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentCopySmallToLongChars(), "Small to long copy assignment string has incorrect characters");

	constexpr bool AssignmentCopyLongToSmallChars() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		string s2 = longstr;
		s2 = s;
		const char* cstr = s2.CStr();
		for (int i = 0; i < 2; i++) {
			if (cstr[i] != smallstr[i]) return false;
		}
		return true;
	}
	TEST_ASSERT(AssignmentCopyLongToSmallChars(), "Long to small copy assignment string has incorrect characters");

	constexpr bool AssignmentCopySmallToSmallLength() {
		const char* smallstr = "a";
		const char* otherSmall = "abcdefg";
		string s = otherSmall;
		string s2 = smallstr;
		s2 = s;
		return s2.Length() == 7;
	}
	TEST_ASSERT(AssignmentCopySmallToSmallLength(), "Small to small copy assignment string has an invalid length");

	constexpr bool AssignmentCopyLongToLongLength() {
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		const char* otherLong = "01234567890123456789012345678901234567890123456789";
		string s = otherLong;
		string s2 = longstr;
		s2 = s;
		return s2.Length() == 50;
	}
	TEST_ASSERT(AssignmentCopyLongToLongLength(), "Long to long copy assignment string has an invalid length");

	constexpr bool AssignmentCopySmallToLongLength() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = longstr;
		string s2 = smallstr;
		s2 = s;
		return s2.Length() == 26;
	}
	TEST_ASSERT(AssignmentCopySmallToLongLength(), "Small to long copy assignment string has an invalid length");

	constexpr bool AssignmentCopyLongToSmallLength() {
		const char* smallstr = "a";
		const char* longstr = "abcdefghijklmnopqrstuvwxyz";
		string s = smallstr;
		string s2 = longstr;
		s2 = s;
		return s2.Length() == 1;
	}
	TEST_ASSERT(AssignmentCopyLongToSmallLength(), "Long to small copy assignment string has an invalid length");
	
#pragma endregion

}
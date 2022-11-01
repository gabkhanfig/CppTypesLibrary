#include "bitset.h"

#define TEST_TYPES "Bitset"
#include <testframework/unit_test_compile_time.h>

namespace BitsetUnitTests 
{

#pragma region Class

	static_assert(sizeof(bitset<1>) == 1, "Tiny bitset does not occupy only 1 byte");
	static_assert(sizeof(bitset<64>) == 8, "Large bitset does not occupy 8 bytes");

#pragma endregion

#pragma region Default_Construct

	constexpr bool DefaultConstruct() {
		bitset<64> b;
		return b.bits == 0;
	}
	TEST_ASSERT(DefaultConstruct(), "Bitset default constructor does not set all flags to 0");

#pragma endregion

#pragma region Flag_Construct

	constexpr bool FlagsConstruct() {
		bitset<64> b = 1;
		return b.bits & 1;
	}
	TEST_ASSERT(FlagsConstruct(), "Bitset flag constructor does not initialize flags");

#pragma endregion

#pragma region Copy_Construct

	constexpr bool CopyConstructSameSize() {
		bitset<64> a = 2;
		bitset<64> b = a;
		return b.bits & 2;
	}
	TEST_ASSERT(CopyConstructSameSize(), "Copy constructor of same sized bitset does not copy flags properly");

	constexpr bool CopyConstructDifferentSize() {
		bitset<1> a = 1;
		bitset<64> b = a;
		return b.bits & 1;
	}
	TEST_ASSERT(CopyConstructDifferentSize(), "Copy constructor of different sized bitset does not copy flags properly");

#pragma endregion

#pragma region Get_Flag

	constexpr bool GetBit() {
		const size_t bitflag = 1 << 7;
		bitset<64> bit = bitflag;
		return bit.GetBit(7);
	}
	TEST_ASSERT(GetBit(), "Getting a bitflag does not get the correct flag");

	constexpr bool GetBitOperator() {
		const size_t bitflag = 1 << 20;
		bitset<64> bit = bitflag;
		return bit[20];
	}
	TEST_ASSERT(GetBitOperator(), "Getting a bitflag from operator[] does not get the correct flag");

#pragma endregion

#pragma region Set_Flag

	constexpr bool SetBit() {
		bitset<64> b;
		b.SetBit(1);
		return b[1];
	}
	TEST_ASSERT(SetBit(), "Setting specific bitflag does not set the correct one");

	constexpr bool SetBitOutOfRange() {
		bitset<8> b;
		b.SetBit(8);
		return !(bool)(b.bits);
	}
	TEST_ASSERT(SetBitOutOfRange(), "Setting specific bitflag out of range sets bit in range");

#pragma endregion

#pragma region Copy_Operator_=

	constexpr bool CopyOperatorOtherNums() {
		bitset<64> b;
		b = 1 << 6;
		return b[6];
	}
	TEST_ASSERT(CopyOperatorOtherNums(), "Copy operator does not copy bits correctly");

	constexpr bool CopyOperatorSameSizeBitset() {
		bitset<64> a;
		bitset<64> b = 4;
		a = b;
		return a[2];
	}
	TEST_ASSERT(CopyOperatorSameSizeBitset(), "Copy operator on same sized bitset does not copy bits correctly");

	constexpr bool CopyOperatorOtherSizeBitset() {
		bitset<64> a;
		bitset<8> b = 4;
		a = b;
		return a[2];
	}
	TEST_ASSERT(CopyOperatorSameSizeBitset(), "Copy operator on different sized bitset does not copy bits correctly");

#pragma endregion

#pragma region Equals_Operator_==

	constexpr bool EqualsOperatorSameSizeBitset() {
		const size_t bitflags = 255;
		bitset<64> b1 = bitflags;
		bitset<64> b2 = bitflags;
		return b1 == b2;
	}
	TEST_ASSERT(EqualsOperatorSameSizeBitset(), "Equivalency check of same sized bitsets failing");

	constexpr bool EqualsOperatorOtherSizeBitset() {
		const size_t bitflags = 255;
		bitset<64> b1 = bitflags;
		bitset<8> b2 = bitflags;
		return b1 == b2;
	}
	TEST_ASSERT(EqualsOperatorOtherSizeBitset(), "Equivalency check of different sized bitsets failing");

	constexpr bool EqualsOperatorFalseDifferentSize() {
		bitset<64> b1 = 511;
		bitset<8> b2 = 255;
		return b1 != b2;
	}
	TEST_ASSERT(EqualsOperatorFalseDifferentSize(), "False equivalency check passing for bitsets of different sizes with the same bits in the smaller range, but different bits outside of range");

#pragma endregion

}
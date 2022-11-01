#pragma once

#include <type_traits>

/* A more size compressed version of std::bitset. Supports bit amounts from 1-64. */
template<size_t bitCount>
struct bitset 
{
	static_assert(bitCount > 0, "bit count must be greater than 0");
	static_assert(bitCount < 65, "bit count must be less than 65");

	typedef std::conditional_t <bitCount <= 8, unsigned char,
		std::conditional_t <bitCount <= 16, unsigned short,
		std::conditional_t<bitCount <= 32, unsigned int,
		unsigned long long >>> Bittype;

	constexpr static size_t GetBitCount() { return bitCount; }

	Bittype bits;

	constexpr bitset() {
		bits = 0;
	}
	
	constexpr bitset(const Bittype initialFlags) {
		bits = initialFlags;
	}

	template<size_t N>
	constexpr bitset(const bitset<N> other) {
		bits = other.bits;
	}

	constexpr bool GetBit(size_t index) {
		return bits >> index & 1U;
	}

	constexpr bool operator [] (size_t index) {
		return GetBit(index);
	}

	constexpr void SetBit(size_t index, bool flag = true) {
		bits ^= ((size_t)(-flag) ^ bits) & 1ULL << index;
	}

	template<size_t N>
	constexpr void operator = (const bitset<N> other) {
		bits = other.bits;
	}

	constexpr void operator = (const Bittype other) {
		bits = other;
	}

	template<size_t N>
	constexpr bool operator == (const bitset<N> other) {
		return (unsigned long long)bits == (unsigned long long)other.bits;
	}

	constexpr bool operator == (Bittype other) {
		return bits == other;
	}
};
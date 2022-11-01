#include "types/string/string.h"
#include "types/array/dynamic_array.h"
#include "types/bitset/bitset.h"
#include <iostream>
#include <vector>

int main() {
	darray<int> a;
	//a.At(5);
	string s(nullptr);
	bitset<1> bit;
	bitset<9> other;
	bit.SetBit(0);
	bit = other;
	std::cout << bit[0] << std::endl;
}
#include "dynamic_array.h"

#define TEST_TYPES "Dynamic Array"
#include <testframework/unit_test_compile_time.h>

#include "../string/string.h"

namespace DynamicArrayUnitTests 
{

#pragma region Class

	static_assert(sizeof(darray<int>) == 16, "Size of darray with T = int is not 16 bytes");

#pragma endregion

#pragma region Default_Constructor

	constexpr bool DefaultConstructValidPtr() {
		darray<int> arr;
		return arr.Data() != nullptr;
	}
	TEST_ASSERT(DefaultConstructValidPtr(), "Default constructor has a null data pointer");
	
	constexpr bool DefaultConstructEmpty() {
		darray<int> arr;
		return arr.Size() == 0;
	}
	TEST_ASSERT(DefaultConstructEmpty(), "Default constructor is not empty");

	constexpr bool DefaultConstructCapacity() {
		darray<int> arr;
		return arr.Capacity() == arr.DEFAULT_CAPACITY;
	}
	TEST_ASSERT(DefaultConstructCapacity(), "Default constructor's capacity is non-default");

#pragma endregion

#pragma region Add_Single

	constexpr bool AddSingleMoveSize() {
		darray<int> arr;
		arr.Add(1);
		return arr.Size() == 1;
	}
	TEST_ASSERT(AddSingleMoveSize(), "Adding single element by move has incorrect size");

	constexpr bool AddSingleMoveElement() {
		darray<int> arr;
		arr.Add(1);
		return arr.Data()[0] == 1;
	}
	TEST_ASSERT(AddSingleMoveElement(), "Adding single element by move has incorrect element");

	constexpr bool AddSingleCopySize() {
		darray<int> arr;
		int b = 1;
		arr.Add(b);
		return arr.Size() == 1;
	}
	TEST_ASSERT(AddSingleCopySize(), "Adding single element by copy has incorrect size");

	constexpr bool AddSingleCopyElement() {
		darray<int> arr;
		int b = 1;
		arr.Add(b);
		return arr.Data()[0] == 1;
	}
	TEST_ASSERT(AddSingleCopyElement(), "Adding single element by copy has incorrect element");

	constexpr bool AddSingleComplexElementMove() {
		darray<string> arr;
		arr.Add(string("abcdefghijklmnopqrstuvwxyz"));
		return arr.Data()[0] == string("abcdefghijklmnopqrstuvwxyz");
	}
	TEST_ASSERT(AddSingleComplexElementMove(), "Adding single complex element by move has incorrect element");

	constexpr bool AddSingleComplexElementCopy() {
		darray<string> arr;
		string str = "aiusdyhlaiusdyhpaisudypaisudypaisudypasud";
		arr.Add(str);
		return arr.Data()[0] == str;
	}
	TEST_ASSERT(AddSingleComplexElementCopy(), "Adding single complex element by copy has incorrect element");

#pragma endregion

#pragma region Add_Multiple_Reallocate

	constexpr bool AddMultiReallocate() {
		darray<int> arr;
		const int oldCapacity = arr.DEFAULT_CAPACITY;
		arr.Add(0);
		arr.Add(1);
		return arr.Capacity() != oldCapacity;
	}
	TEST_ASSERT(AddMultiReallocate(), "Array does not reallocate a greater capacity with default capacity of 1, and adding multiple elements");

	constexpr bool AddMultiReallocateElements() {
		darray<int> arr;
		arr.Add(50);
		arr.Add(100);
		return arr[0] == 50 && arr[1] == 100;
	}
	TEST_ASSERT(AddMultiReallocateElements(), "Adding multiple elements and having array resize does not keep the same elements");

	constexpr bool AddMultiReallocateComplexElement() {
		darray<string> arr;
		string s1 = "hello world!";
		string s2 = "another very very long string probably";
		arr.Add(s1);
		arr.Add(s2);
		return arr[0] == s1 && arr[1] == s2;
	}
	TEST_ASSERT(AddMultiReallocateComplexElement(), "Adding multiple complex elements and having array resize does not keep the same elements");

#pragma endregion

#pragma region Index

	constexpr bool GetIndexInRange() {
		darray<int> arr;
		for (int i = 0; i < 100; i++) {
			arr.Add(i);
		}
		for (int i = 0; i < 100; i++) {
			if (arr[i] != i) return false;
		}
		return true;
	}
	TEST_ASSERT(GetIndexInRange(), "Array indexing has incorrect elements");

#pragma endregion



}
#pragma once

#include <utility>
#include <stdexcept>

/* Array integer type */
typedef unsigned int arrint;

template<typename T>
struct darray 
{
private:

	T* data;
	arrint size;
	arrint capacity;

public:

	static constexpr arrint DEFAULT_CAPACITY = 1;

	/* @return The number of elements currently held in the array. */
	constexpr arrint Size() const {
		return size;
	}

	/* @return The capacity of the allocated data. */
	constexpr arrint Capacity() const {
		return capacity;
	}

	/* DANGEROUS. @return Raw array data pointer. */
	constexpr T* Data() {
		return data;
	}

private:

	constexpr void Reallocate() {
		const arrint newCapacity = capacity * 2;

		T* newData = new T[newCapacity];
		for (arrint i = 0; i < Size(); i++) {
			newData[i] = std::move(data[i]);
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

public:

	constexpr darray() {
		data = new T[DEFAULT_CAPACITY];
		size = 0;
		capacity = DEFAULT_CAPACITY;
	}

	constexpr ~darray() {
		if (data != nullptr)
			delete[] data;
	}

	/* If the new capacity is less than the array's current capacity, this function does nothing. */
	constexpr void Reserve(arrint newCapacity) {
		if (newCapacity < capacity) return;

		T* newData = new T[newCapacity];
		for (arrint i = 0; i < Size(); i++) {
			newData[i] = std::move(data[i]);
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	constexpr T& At(arrint index) {
		if (index >= Size()) {
			//if (std::is_constant_evaluated()) {
			//}
			throw std::out_of_range("Array element At() index is out of bounds!");
		}

		return data[index];
	}

	constexpr T& operator [] (arrint index) {
		return At(index);
	}

	constexpr void Add(T&& element) {
		if (size == capacity) {
			Reallocate();
		}

		data[size] = std::move(element);
		size++;
	}

	constexpr void Add(const T& element) {
		if (size == capacity) {
			Reallocate();
		}

		data[size] = element;
		size++;
	}




};
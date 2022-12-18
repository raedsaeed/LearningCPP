#pragma once

#include "pch.h"

template<typename T, size_t size>
class Array {
public:

	constexpr size_t getSize() const { return size; }

	T& operator[] (size_t index) {
		return mData[index];
	}

	const T& operator[](size_t index) const {
		return mData[index];
	}


	T* getDat() { return mData; }

	const T* getData() const { return mData; }

private:
	T mData[size];
};
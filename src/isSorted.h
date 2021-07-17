#pragma once
#include <iostream>

template <typename DataType, typename LenType>
bool isSorted(DataType* data, LenType length) {
	length--;
	for (int i = 0; i < length; i++) {
		if (data[i] > data[i + 1]) {
			std::cout << "Unsorted at: " << i << "\n";
			return 0;
		}
	}
	return 1;
}
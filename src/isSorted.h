#pragma once

template <typename DataType, typename LenType>
bool isSorted(DataType* data, LenType length) {
	length--;
	for (int i = 0; i < length; i++) {
		if (data[i] > data[i + 1])
			return 0;
	}
	return 1;
}
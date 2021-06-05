#pragma once

template <typename DataType, typename LenType>
void InsersionSort(DataType* data, LenType length) {
	length--;

	
	// run through array
	for (LenType startingIndex = 0; startingIndex < length; startingIndex++) {
		LenType i = startingIndex;
		
		// move to front until smaller value is reached
		while (data[i] > data[i + 1] && i>=0) {
			DataType temp = data[i];
			data[i] = data[i + 1];
			data[i + 1] = temp;
			i--;
		}
	}
}
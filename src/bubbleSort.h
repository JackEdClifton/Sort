#pragma once

template <typename DataType, typename LenType>
void BubbleSort(DataType* data, LenType length) {
	
	bool unsorted = true;

	// run through array until sorted
	while (unsorted) {
		unsorted = false;
		length--;

		// iterate through each position
		for (LenType i = 0; i < length; i++) {
			
			// check if values should be swaped
			if (data[i] > data[i+1]) {
				unsorted = true;
				
				// swapping values
				DataType temp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = temp;
			}
		}
	}
}
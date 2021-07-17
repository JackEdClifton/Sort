#pragma once

void RadixSort(int* data, const int& length) {

	// array to temporarily store values after each iteration
	int* buffer = new int[length];

	// idk
	int bitToCompare = 1;

	// iterate through each bit position
	for (int bitSignificance = 0; bitSignificance < sizeof(int) * 8; bitSignificance++) {
		
		// count occurances
		int numOf0s = 0;
		int numOf1s = 0;
		for (int i = 0; i < length; i++) {
			if (!(data[i] & bitToCompare))
				numOf1s++;
		}

		// skip iteration if already sorted
		if (!numOf1s)
			continue;

		// sort array to buffer
		for (int i = 0; i < length; i++) {
			if (data[i] & bitToCompare) {
				buffer[numOf1s] = data[i];
				numOf1s++;
			}
			else {
				buffer[numOf0s] = data[i];
				numOf0s++;
			}
		}

		// push buffer to actuall array
		for (int i = 0; i < length; i++) {
			data[i] = buffer[i];
		}
		
		bitToCompare <<= 1;
	}
	delete[] buffer;
}
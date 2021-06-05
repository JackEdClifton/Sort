#pragma once

#include <vector>
#include "isSorted.h"

template <typename LenType>
struct indexRange {
	LenType now = 0;
	LenType max = 0;

	indexRange(LenType a, LenType b) {
		now = a;
		max = b;
	}

	bool outOfRange() {
		return now > max;
	}
};

template <typename DataType, typename LenType>
void MergeSort(DataType* data, LenType length) {

	// escape early if already sorted
	if (isSorted(data, length)) return;

	// duplicate array to temporarily store sorted values
	std::vector<DataType> buffer;
	buffer.resize(length);


	// run first iteration without indexRange to save memory
	for (LenType i = 0; i < length; i += 2) {
		if (data[i] > data[i + 1]) {
			DataType temp = data[i];
			data[i] = data[i + 1];
			data[i + 1] = temp;
		}
	}

	// loop through group sizes
	for (LenType groupSize = 2; groupSize < length; groupSize *= 2) {
	
		// get indexes for comparing
		std::vector<indexRange<LenType>> comparisons;
		for (LenType i = 0; i < length; i += groupSize) {
			
			LenType maxValue;
			if (i + groupSize <= length) maxValue = i + groupSize;
			else maxValue = length;

			comparisons.push_back(indexRange<LenType>(i, maxValue - 1));
		}

		// add empty index range
		if (comparisons.size() % 2) {
			comparisons.push_back(indexRange<LenType>(1, 0));
		}

		// sort each group to buffer
		for (LenType groupStartingIndex = 0; groupStartingIndex < length; groupStartingIndex += groupSize*2) {

			// get subgroup things
			LenType i = groupStartingIndex / groupSize;
			auto leftSubGroup = comparisons[i];
			auto rightSubGroup = comparisons[i+1];

			// sort values to buffer
			for (LenType i = 0; i < groupSize*2; i++) {

				// get values for iteration
				LenType bufferIndex = groupStartingIndex + i;
				DataType leftVal = data[leftSubGroup.now];
				DataType rightVal = data[rightSubGroup.now];

				// check there is a valid index
				if (leftSubGroup.outOfRange() && rightSubGroup.outOfRange())
					break;

				// check if right group is out of range
				if (rightSubGroup.outOfRange()) {
					buffer[bufferIndex] = leftVal;
					leftSubGroup.now++;
					continue;
				}

				// check if left group is out of range
				if (leftSubGroup.outOfRange()) {
					buffer[bufferIndex] = rightVal;
					rightSubGroup.now++;
					continue;
				}

				// find smallest value in group
				if (leftVal <= rightVal) {
					buffer[bufferIndex] = leftVal;
					leftSubGroup.now++;
				}
				else if (rightVal <= leftVal) {
					buffer[bufferIndex] = rightVal;
					rightSubGroup.now++;
				}
			}
		}
		// push buffer to array
		for (LenType i = 0; i < length; i++) {
			data[i] = buffer[i];
		}
	}
}
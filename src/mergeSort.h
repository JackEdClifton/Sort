#pragma once
#include <iostream>
#include <thread>
#include <vector>


//template <typename int>
struct indexRange {
	int now = 0;
	int max = 0;

	indexRange(int a, int b) : now(a), max(b) {}

	bool outOfRange() {
		return now > max;
	}

	void operator++(int) {
		now++;
	}
};

template <typename DataType>  //, typename int>
void MergeSort(DataType* data, int length, int startIndex = 0, int startGroupSize = 2) {

	// array to temporarily store values after each iteration
	DataType* buffer = new DataType[length];

	// run first iteration without indexRange to save memory
	for (int i = startIndex; i < length + startIndex; i += 2) {
		if (data[i] > data[i + 1]) {
			DataType temp = data[i];
			data[i] = data[i + 1];
			data[i + 1] = temp;
		}
	}

	// loop through group sizes
	for (int groupSize = startGroupSize; groupSize < length; groupSize *= 2) {

		// get indexes for comparing
		std::vector<indexRange> comparisons;
		for (int i = 0; i < length; i += groupSize) {

			int maxValue;
			if (i + groupSize <= length)
				maxValue = i + groupSize;
			else
				maxValue = length;

			comparisons.push_back(indexRange(i, maxValue - 1));
		}

		// add empty obj incase the length is odd
		if (comparisons.size() % 2)
			comparisons.push_back(indexRange(1, 0));

		// sort each group to buffer
		for (int groupStartingIndex = 0; groupStartingIndex < length; groupStartingIndex += groupSize * 2) {

			// get subgroup things
			int i = groupStartingIndex / groupSize;
			indexRange leftSubGroup = comparisons[i];
			indexRange rightSubGroup = comparisons[i + 1];

			// sort values to buffer
			const int timesToLoop = groupSize * 2;
			for (int i = 0; i < timesToLoop; i++) {

				// get values for iteration
				int bufferIndex = groupStartingIndex + i;
				DataType leftVal = data[leftSubGroup.now + startIndex];
				DataType rightVal = data[rightSubGroup.now + startIndex];

				// check there is a valid index
				if (leftSubGroup.outOfRange() && rightSubGroup.outOfRange())
					break;

				// check if right group is out of range
				if (rightSubGroup.outOfRange()) {
					buffer[bufferIndex] = leftVal;
					leftSubGroup++;
					continue;
				}

				// check if left group is out of range
				if (leftSubGroup.outOfRange()) {
					buffer[bufferIndex] = rightVal;
					rightSubGroup++;
					continue;
				}

				// increment the smallest indexRange in group
				if (leftVal <= rightVal) {
					buffer[bufferIndex] = leftVal;
					leftSubGroup++;
				}
				else if (rightVal <= leftVal) {
					buffer[bufferIndex] = rightVal;
					rightSubGroup++;
				}
			}
		}

		// push buffer to array
		for (int i = 0; i < length; i++) {
			data[i + startIndex] = buffer[i];
		}
	}
	delete[] buffer;
}


// uses ^function^ but with more cores and moar POWARR
template <typename DataType>
void AsyncMergeSort(DataType* data, int length) {

#if 1
	int maxThreads = 8;
	for (int numOfThreads = maxThreads; numOfThreads; numOfThreads /= 2) {
		std::thread* threads = new std::thread[numOfThreads];

		// if its not on the first set of threads then skip the first part
		int groupSize;
		if (numOfThreads == maxThreads)
			groupSize = 2;
		else
			groupSize = length / (numOfThreads * 2);

		// loop through the threads
		for (int thread = 0; thread < numOfThreads; thread++) {

			// add new thread to list
			threads[thread] = std::thread ([&]() { MergeSort(
				data,
				length / numOfThreads,
				(length / numOfThreads) * thread,
				groupSize
			); });

			// sometimes an error happens, not sure how but waiting a bit seems to unreliably fix it
			std::this_thread::sleep_for(std::chrono::microseconds(500000));
		}

		// wait for threads to complete
		for (int i = 0; i < numOfThreads; i++)
			threads[i].join();
		
		// cant be leaking that memory
		delete[] threads;
	}
	
	// a more... reliable way of the thing ^above^
#else	
	int halfLength = length / 2;
	int quarterLength = length / 4;

	// use 4 cores
	std::thread t1([&]() { MergeSort(data, quarterLength, 0); });
	std::thread t2([&]() { MergeSort(data, quarterLength, quarterLength); });
	std::thread t3([&]() { MergeSort(data, quarterLength, halfLength); });
	std::thread t4([&]() { MergeSort(data, quarterLength, halfLength + quarterLength); });
	t1.join(); t2.join(); t3.join(); t4.join();


	// use 2 cores
	std::thread t5([&]() { MergeSort(data, halfLength, 0, quarterLength); });
	std::thread t6([&]() { MergeSort(data, halfLength, halfLength, quarterLength); });
	t5.join(); t6.join();


	// use 1 core
	std::thread t7([&]() { MergeSort(data, length, 0, halfLength); });
	t7.join();
	
#endif
}

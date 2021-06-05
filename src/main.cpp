
// modules
#include <iostream>
#include <chrono>
#include "sort.h"

// get accurate unix time
double unixTime() {
	return static_cast<double>
		(std::chrono::duration_cast<std::chrono::microseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000000.0;
}

// example of sorting
void example() {
	
	// benchmarking
	double startTime, endTime, sortTime;

	// create array
	std::cout << "Creating Array\n";
	const int LEN = 100000;
	const int MAX = 1000000;
	const int MIN = -1000000;
	int* data = new int[LEN];

	// assign random values to array
	std::cout << "Randomizing Array\n";
	srand(static_cast<int>(unixTime()));
	for (int i = 0; i < LEN; i++)
		data[i] = (rand() % (MAX-MIN)) + MIN;

	// sort array and log duration
	std::cout << "Sorting " << LEN << " items\n";
	startTime = unixTime();
	MergeSort(data, LEN);
	endTime = unixTime();
	sortTime = endTime - startTime;
	std::cout << "Array Sorted in " << sortTime << "s\n";
}


// program entry point
int main() {
	const double PROGRAM_START_TIME = unixTime();
	example();
	std::cout << "[Program Finished in " << unixTime() - PROGRAM_START_TIME << "s]";
	std::cin.get();
}


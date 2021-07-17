
// modules
#include <iostream>

// std::chrono for getting time
#include <chrono>

// headers for sorting arrays
#include "isSorted.h"
#include "mergeSort.h"
#include "radixSort.h"


// get accurate unix time
double unixTime() {
	return static_cast<double>(
		std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count()
	) / 1000000.0;
}

// example of sorting
void example(const int LEN = 500000, const int MIN = 0, const int MAX = 1000) {
	
	// create random array
	int* data = new int[LEN];
	srand(static_cast<int>(unixTime()));
	for (int i = 0; i < LEN; i++)
		data[i] = (rand() % (MAX-MIN)) + MIN;

	
	// sort array and log duration
	double startTime = unixTime();
	RadixSort(data, LEN);
	double endTime = unixTime();

	std::cout << endTime - startTime << std::endl;;

	// validate
	std::cout << "Errors: ";
	int errors = 0;
	for (int i = 1; i < LEN; i++) {
		if (data[i - 1] > data[i])
			errors++;
	}
	std::cout << errors << std::endl << std::endl;

	// validate
	//if (!isSorted(data, LEN)) std::cout << "WARNING: array not in order" << std::endl;

	delete[] data;
}


// program entry point
int main() {

	const double PROGRAM_START_TIME = unixTime();
	std::cout << std::fixed;
	while (true)
		example();
	std::cout << "[Program Finished in " << unixTime() - PROGRAM_START_TIME << "s]";
	std::cin.get();
}


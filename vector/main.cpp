#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector.hpp>
#include <iterator.hpp>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void insertRandomInt(int& a){ a = std::rand() % 100000; }

int main(){

	using std::cout;

	std::time_t start = std::time(NULL);

	// testing vector<int>
	std::srand(42);
	
	int intArrSize = 1000000;
	int* arr = new int[intArrSize];

	std::for_each(arr, arr + intArrSize, insertRandomInt);

	/* test reverse_iterator with raw pointers */

	// testing vector<string>

	std::time_t end = std::time(NULL);

	std::fstream executionTime("vector execution time",
		std::fstream::app | std::fstream::out);

	executionTime << "ft::vector run time: " << double(end) - start
		<< " seconds\n";
	
	executionTime.close();

}

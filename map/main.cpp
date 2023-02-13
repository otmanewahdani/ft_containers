/* this file contains tests of the ft::map container class.
	these tests are meant to produce the same output as std::map
	in order to demonstrate that ft::map is a re-implementation of 
	its STL counterpart */

#include <map>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <utility.hpp>
#include <map.hpp>
#include <pairTests.hpp>

using std::string;
using std::cout;

int main(){

	std::time_t start = std::time(NULL);

	runPairtests();

	std::fstream executionTime("map execution time",
		std::fstream::app | std::fstream::out);

	std::time_t end = std::time(NULL);

	executionTime << "ft::map run time: " << double(end) - start
		<< " seconds\n";
	
	executionTime.close();

	return 0;

}

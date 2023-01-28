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
#include <iterator>

using std::cout;
using std::string;
using std::stringstream;
using std::ostream_iterator;
using std::istream_iterator;

void insertRandomInt(int& a){ a = std::rand() % 100000; }

string intToString(const int& i){
	stringstream converter;
	converter << i << " ";
	return converter.str();
}

int main(){


	std::time_t start = std::time(NULL);

	// testing vector<int>
	std::srand(42);
	
	int intArrSize = 1000000;
	int* arr = new int[intArrSize];

	std::for_each(ft::reverse_iterator<int*>(arr + intArrSize),
		ft::reverse_iterator<int*>(arr), insertRandomInt);

	ft::vector<int> intVec1(arr, arr + intArrSize);
	const ft::vector<int> constIntVec(1000000, 67);
	ft::vector<int> intVec2(constIntVec);
	intVec2.assign(constIntVec.begin(), constIntVec.end());
	intVec2 = intVec1;

	stringstream strOfInts;
	std::transform(intVec2.begin(), intVec2.end(),
		ostream_iterator<string>(strOfInts), intToString);
	istream_iterator<int> inputIt(strOfInts);
	ft::vector<int> intVec3(inputIt, istream_iterator<int>());

	insertRandomInt(intVec1.at(intVec1.size() - 1));
	cout << constIntVec.at(constIntVec.size() - 1) << '\n';
	try{
		intVec1.at(intVec1.size());
	}
	catch(std::exception& e){
		cout << "exception 1 caucht successfully\n";
	}

	cout << (intVec2.front() = std::rand() % 1000000) << '\n';
	cout << constIntVec.front() << '\n';
	cout << (intVec1.back() = std::rand() % 1000000) << '\n';
	cout << constIntVec.back() << '\n';

	cout << intVec3.empty() << '\n';
	cout << intVec1.size() << '\n';
	cout << intVec2.size() << '\n';
	cout << intVec3.size() << '\n';
	cout << intVec3.capacity() << '\n';

	intVec1.reserve(intVec1.capacity());
	intVec2.reserve(intVec2.capacity() * 2);
	intVec3.reserve(intVec3.capacity() / 2);
	cout << intVec3.capacity() << '\n';
	cout << intVec2.capacity() << '\n';
	cout << intVec1.capacity() << '\n';

	// print intVec1
	for (ft::vector<int>::const_iterator it = intVec1.begin();
		it != intVec1.end(); ++it)
		cout << *it << '\n';

	// reverse print intVec2
	for (ft::vector<int>::const_reverse_iterator it = intVec2.rbegin();
		it != intVec2.rend(); ++it)
		cout << *it << '\n';
	
	// print intVec3
	for (ft::vector<int>::iterator it = intVec3.begin();
		it != intVec3.end(); ++it)
		cout << *it << '\n';

	// print constIntVec
	for (ft::vector<int>::size_type i = 0; i < constIntVec.size(); ++i)
		cout << constIntVec[i] << '\n';


	// testing vector<string>

	delete arr;


	std::fstream executionTime("vector execution time",
		std::fstream::app | std::fstream::out);

	std::time_t end = std::time(NULL);

	executionTime << "ft::vector run time: " << double(end) - start
		<< " seconds\n";
	
	executionTime.close();

}

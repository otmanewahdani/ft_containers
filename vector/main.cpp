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

static void insertRandomInt(int& a){ a = std::rand() % 100000; }

static string intToString(const int& i){
	stringstream converter;
	converter << i << " ";
	return converter.str();
}

static void insertRandomString(string& str) {

	static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

	const int len = rand() % 200;
	str.reserve(len);

    for (int i = 0; i < len; ++i)
		str += alphanum[rand() % (sizeof(alphanum) - 1)];

}

inline bool isLenLess100(const string& str){ return str.length() < 100; }

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
	intVec3.reserve(intVec3.capacity() - 1);
	cout << intVec3.capacity() << '\n';
	cout << intVec2.capacity() << '\n';
	cout << intVec1.capacity() << '\n';

	intVec2.clear();
	cout << *intVec1.insert(intVec1.begin(), 42) << '\n';
	cout << *intVec2.insert(intVec2.end(), 42) << '\n';
	cout << *intVec3.insert(intVec3.begin() + intVec3.size() / 2, 42) << '\n';
	intVec1.insert(intVec1.begin(), 10000, 1337);
	intVec2.insert(intVec2.end(), 10000, 1337);
	intVec3.insert(intVec3.begin() + intVec3.size() / 2, 10000, 1337);
	intVec1.insert(intVec1.begin(), constIntVec.begin()
		+ constIntVec.size() / 3, constIntVec.end());
	intVec2.insert(intVec2.end(), intVec3.rbegin() +
		intVec3.size() / 4, intVec3.rend());
	strOfInts.clear();
	std::transform(arr, arr + intArrSize,
		ostream_iterator<string>(strOfInts), intToString);
	inputIt = strOfInts;
	intVec3.insert(intVec3.begin() + intVec3.size() / 3,
		inputIt, istream_iterator<int>());

	cout << *intVec1.erase(intVec1.begin()) << '\n';
	cout << (intVec2.erase(intVec2.end() - 1) == intVec2.end()) << '\n';
	cout << *intVec3.erase(intVec3.begin() + intVec2.size() / 2) << '\n';
	cout << (intVec1.erase(intVec1.end() - 100, intVec1.end()) == intVec1.end()) << '\n';
	cout << (intVec1.erase(intVec1.begin(), intVec1.begin()) == intVec1.begin()) << '\n';
	cout << *intVec2.erase(intVec2.begin(), intVec2.begin() + 200) << '\n';
	cout << *intVec3.erase(intVec3.begin() + intVec3.size() / 2,
		intVec3.begin() + intVec3.size() / 2 + 2000) << '\n';
	
	intVec1.push_back(42);
	intVec3.push_back(1337);
	for (ft::vector<int>::size_type newSize = intVec2.capacity() * 5,
		i = 0; i < newSize; ++i)
		intVec2.push_back(rand() % 10000);

	// remove count elems
	for (ft::vector<int>::size_type count = intVec1.size() / 2,
		i = 0; i < count; ++i)
		intVec1.pop_back();
	for (ft::vector<int>::size_type count = intVec2.size() / 4,
		i = 0; i < count; ++i)
		intVec2.pop_back();
	for (ft::vector<int>::size_type count = intVec3.size() / 3,
		i = 0; i < count; ++i)
		intVec3.pop_back();
	
	intVec1.resize(intVec2.size() - intVec2.size() / 5);
	intVec3.resize(intVec3.size() * 2);
	intVec2.resize(intVec2.size());

	intVec1.swap(intVec3);
	intVec2.swap(intVec1);
	intVec3.swap(intVec2);
	std::swap(intVec1, intVec3);
	std::swap(intVec2, intVec3);
	std::swap(intVec2, intVec1);

	const ft::vector<int>* intVecs[] = {
		&intVec1,
		&intVec2,
		&intVec3,
		&constIntVec
	};

	// equality
	for (int i = 0; i < 4; ++i)
		cout << (intVec1 == *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec2 == *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec3 == *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (constIntVec == *intVecs[i]) << '\n';
	
	//inequality
	for (int i = 0; i < 4; ++i)
		cout << (intVec1 != *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec2 != *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec3 != *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (constIntVec != *intVecs[i]) << '\n';
	
	// less than
	for (int i = 0; i < 4; ++i)
		cout << (intVec1 < *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec2 < *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec3 < *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (constIntVec < *intVecs[i]) << '\n';
	
	// less than or equal
	for (int i = 0; i < 4; ++i)
		cout << (intVec1 <= *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec2 <= *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec3 <= *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (constIntVec <= *intVecs[i]) << '\n';
	
	// greater than
	for (int i = 0; i < 4; ++i)
		cout << (intVec1 > *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec2 > *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec3 > *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (constIntVec > *intVecs[i]) << '\n';
	
	// greater than or equal
	for (int i = 0; i < 4; ++i)
		cout << (intVec1 >= *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec2 >= *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (intVec3 >= *intVecs[i]) << '\n';
	for (int i = 0; i < 4; ++i)
		cout << (constIntVec >= *intVecs[i]) << '\n';

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

	delete arr;

	// testing vector<string>
	const int strVecSize = 1000000;

	ft::vector<string> strVec1(strVecSize);

	std::for_each(strVec1.begin(), strVec1.end(), insertRandomString);
	
	ft::vector<string> strVec2(strVec1.rbegin(), 
		strVec1.rbegin() + strVec1.size() / 4);

	strVec2 = strVec1;

	strVec1.insert(strVec1.begin(), strVec2.begin()
		+ strVec2.size() - strVec2.size() / 4, strVec2.end());

	cout << *strVec2.erase(strVec2.begin() + strVec2.size() / 2,
		strVec2.begin() + strVec2.size() / 2 + strVec2.size() / 10) << '\n';

	cout << std::count_if(strVec1.begin(), strVec1.end(), isLenLess100) << '\n';
	cout << std::count_if(strVec2.rbegin(), strVec2.rend(), isLenLess100) << '\n';
	cout << *std::search(strVec1.begin(), strVec1.end(),
		strVec1.begin() + 1000, strVec1.begin() + 2000) << '\n';
	
	std::copy(strVec2.begin() + strVec2.size() / 2,
		strVec2.begin() + strVec2.size() / 2 + 10000,
		strVec1.begin() + strVec1.size() / 3);

	string tmpStr;
	insertRandomString(tmpStr);
	std::replace_if(strVec2.begin() + 50,
		strVec2.begin() + strVec2.size() / 2,
		isLenLess100, tmpStr);

	std::reverse(strVec1.begin() + strVec1.size() / 3,
		strVec1.begin() + strVec1.size() / 2);

	std::rotate(strVec2.begin(), strVec2.begin() + strVec2.size() / 5,
		strVec2.begin() + strVec2.size() / 3);

	std::sort(strVec1.begin() + strVec1.size() / 2,
		strVec1.begin() + strVec1.size() / 2 + strVec1.size() / 10);

	std::sort(strVec2.begin(), strVec2.begin() + strVec2.size() / 10);

	std::swap(strVec1, strVec2);

	// print strVec1
	for (ft::vector<string>::const_reverse_iterator it
		 = strVec1.rbegin(); it != strVec1.rend(); ++it)
		cout << *it << '\n';

	// print strVec2
	for (ft::vector<string>::const_iterator it = strVec2.begin();
		it != strVec2.end(); ++it)
		cout << *it << '\n';

	std::fstream executionTime("vector execution time",
		std::fstream::app | std::fstream::out);

	std::time_t end = std::time(NULL);

	executionTime << "ft::vector run time: " << double(end) - start
		<< " seconds\n";
	
	executionTime.close();

}

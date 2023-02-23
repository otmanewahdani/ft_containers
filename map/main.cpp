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
#include <memory>
#include <vector>
#include <algorithm>

using std::string;
using std::cout;
using std::less;
using std::greater;
using std::vector;
using std::for_each;

void insertRandomInt(int& a){ a = std::rand() % 100000; }

template <class T, class U>
void printPair(const ft::pair<T, U>& pairObj){

	cout << pairObj.first << " " << pairObj.second << '\n';

}

int main(){

	std::time_t start = std::time(NULL);

	// testing ft::pair and ft::make_pair
	runPairtests();
	cout << "end of pair tests\n\n";

	/******* types used in tests *******/
	// comparison objects types
	typedef less<int> Less;
	typedef greater<int> Greater;

	// making a keyVectorSize amount of unique int keys
	const int keyVectorSize = 5000;
	vector<int> keyVector;
	keyVector.reserve(keyVectorSize);
	for (int i = 0; i < keyVectorSize; ++i)
		keyVector.push_back(i);
	std::random_shuffle(keyVector.begin(), keyVector.end());
	
	// making a randomIntsVecSize amount of random ints
	const int randomIntsVecSize = keyVectorSize;
	vector<int> randomIntsVec(randomIntsVecSize);
	std::for_each(randomIntsVec.begin(), randomIntsVec.end(),
		insertRandomInt);

	// testing map with value_type of pair<int, int>
	{
		/******* types used in tests *******/
		// map::value_type aka pair
		typedef ft::pair<const int, int> PairVal;

		// allocator type
		typedef std::allocator< PairVal > Allocator;

		// making a vector of a keyVectorSize amount of
			// ft::pair<int, int> elements
		vector< ft::pair<int, int> > doubleIntPairVec;
		doubleIntPairVec.reserve(keyVectorSize);
		for (size_t i = 0; i < keyVector.size(); ++i)
			doubleIntPairVec.push_back(
				ft::make_pair(keyVector[i], randomIntsVec[i]) );

		// testing with comparator of type std::less
		{

			/******* types used in tests *******/
			// map type
			typedef ft::map<int, int> Map;

			// iterators types
			typedef Map::iterator Iter;
			typedef Map::const_iterator ConstIter;
			//typedef Map::reverse_iterator RevIter;
			//typedef Map::const_reverse_iterator ConstRevIter;

			// insert return type
			typedef ft::pair< Iter, bool> InsertPair;

			/******* start of actual tests *******/

			// testing simple constructors
			{
				Map map1(Less());
				Map map2(Less(), Allocator());
			}

			Map map1;

			/******* testing map(first, last) *******/
			const Map map2(doubleIntPairVec.begin(),
				doubleIntPairVec.begin() + doubleIntPairVec.size() / 2);

			/******* testing copy constructor *******/
			Map map3(map2);

			/******* testing copy assignment operator *******/
			map3 = map1;

			/******* testing insert(value) *******/ 
			InsertPair insertRet;
			for (size_t i = 0; i < doubleIntPairVec.size(); ++i){

				insertRet = map1.insert(doubleIntPairVec[i]);
				cout << insertRet.first->first << " " << 
					insertRet.first->second << " " << insertRet.second << '\n';

			}

			insertRet = map1.insert(*doubleIntPairVec.begin());
			cout << insertRet.first->first << " " << 
				insertRet.first->second << " " << insertRet.second << '\n';

			insertRet = map1.insert( *(doubleIntPairVec.begin()
				+ doubleIntPairVec.size() / 2) );
			cout << insertRet.first->first << " " << 
				insertRet.first->second << " " << insertRet.second << '\n';
			cout << '\n';

			/******* testing insert(iterator, value) *******/
			Map map4;

			ConstIter cIter = map4.insert(map4.begin(), *doubleIntPairVec.begin());
			cout << cIter->first << " " << cIter->second << '\n';

			cIter = map4.insert(map4.begin(), *(doubleIntPairVec.begin()
				+ doubleIntPairVec.size() / 2) );
			cout << cIter->first << " " << cIter->second << '\n';

			cIter = map4.insert(map4.begin(), *doubleIntPairVec.begin());
			cout << cIter->first << " " << cIter->second << '\n';

			/******* testing insert(first, last) *******/ 
			map4.insert(doubleIntPairVec.begin(),
				doubleIntPairVec.end());

			/******* testing copy assignment operator *******/
			map3 = map4;

			/******* printing map's elements *******/
			// in order
			for_each(map1.begin(), map1.end(), printPair<const int, int>);
			for_each(map2.begin(), map2.end(), printPair<const int, int>);
			for_each(map3.begin(), map3.end(), printPair<const int, int>);
			for_each(map4.begin(), map4.end(), printPair<const int, int>);

			// in reverse order
			for_each(map1.rbegin(), map1.rend(), printPair<const int, int>);
			for_each(map2.rbegin(), map2.rend(), printPair<const int, int>);
			for_each(map3.rbegin(), map3.rend(), printPair<const int, int>);
			for_each(map4.rbegin(), map4.rend(), printPair<const int, int>);

		} // end of testing with comparator of type std::less

		// testing with comparator of type std::greater
		{
			/******* types used in tests *******/
			// map type
			typedef ft::map<int, int, Greater> Map;

			// iterators types
			typedef Map::iterator Iter;
			typedef Map::const_iterator ConstIter;
			typedef Map::reverse_iterator RevIter;
			typedef Map::const_reverse_iterator ConstRevIter;

			// insert return type
			typedef ft::pair< Iter, bool> InsertPair;

			/******* start of actual tests *******/

			// testing simple constructors
			{
				Map map1(Greater());
				Map map2(Greater(), Allocator());
			}

			Map map1;

			/******* testing map(first, last) *******/
			Map map2(doubleIntPairVec.begin(),
				doubleIntPairVec.begin() + doubleIntPairVec.size() / 2);

			/******* testing copy constructor *******/
			Map map3(map2);

			/******* testing insert(value) *******/ 
			InsertPair insertRet;
			for (size_t i = 0; i < doubleIntPairVec.size(); ++i){

				insertRet = map1.insert(doubleIntPairVec[i]);
				cout << insertRet.first->first << " " << 
					insertRet.first->second << " " << insertRet.second << '\n';

			}

			insertRet = map1.insert(*doubleIntPairVec.begin());
			cout << insertRet.first->first << " " << 
				insertRet.first->second << " " << insertRet.second << '\n';

			insertRet = map1.insert( *(doubleIntPairVec.begin()
				+ doubleIntPairVec.size() / 2) );
			cout << insertRet.first->first << " " << 
				insertRet.first->second << " " << insertRet.second << '\n';

			/******* testing insert(iterator, value) *******/
			Map map4;

			ConstIter cIter = map4.insert(map4.begin(), *doubleIntPairVec.begin());
			cout << cIter->first << " " << cIter->second << '\n';

			cIter = map4.insert(map4.begin(), *(doubleIntPairVec.begin()
				+ doubleIntPairVec.size() / 2) );
			cout << cIter->first << " " << cIter->second << '\n';

			cIter = map4.insert(map4.begin(), *doubleIntPairVec.begin());
			cout << cIter->first << " " << cIter->second << '\n';

			/******* testing insert(first, last) *******/ 
			map4.insert(doubleIntPairVec.begin(),
				doubleIntPairVec.end());

			/******* testing swap *******/ 
			map4.swap(map2);

			/******* testing iterators *******/ 
			Iter it1;

			Iter it2 = map1.begin();

			it2->second = 10;

			ConstIter constIt(it2);

			const Iter constNormalIt(map2.begin());

			constIt = map2.begin();

			it1 = constNormalIt;

			RevIter rit(map3.rbegin());

			ConstRevIter constRit(rit);

			/******* printing map's elements *******/
			// in order
			for_each(map1.begin(), map1.end(), printPair<const int, int>);
			for_each(map2.begin(), map2.end(), printPair<const int, int>);
			for_each(map3.begin(), map3.end(), printPair<const int, int>);
			for_each(map4.begin(), map4.end(), printPair<const int, int>);

			// in reverse order
			for_each(map1.rbegin(), map1.rend(), printPair<const int, int>);
			for_each(map2.rbegin(), map2.rend(), printPair<const int, int>);
			for_each(map3.rbegin(), map3.rend(), printPair<const int, int>);
			for_each(map4.rbegin(), map4.rend(), printPair<const int, int>);

		} // end of testing with comparator of type std::greater

	} // end of testing map with value_type of pair<int, int>

	std::fstream executionTime("map execution time",
		std::fstream::app | std::fstream::out);

	std::time_t end = std::time(NULL);

	executionTime << "ft::map run time: " << double(end) - start
		<< " seconds\n";
	
	executionTime.close();

	return 0;

}

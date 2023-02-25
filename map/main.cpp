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
#include <limits>
#include <vector>
#include <algorithm>

using std::string;
using std::cout;
using std::less;
using std::greater;
using std::vector;
using std::for_each;

// max of number of elements to test
const int MAX_ITEMS = 1000;

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
	const int keyVectorSize = MAX_ITEMS;
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

		// printing functions
		typedef void (*PrintPairFun)(const ft::pair<const int, int>&);
		PrintPairFun printPairFunPtr = printPair<const int, int>;

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

			/******* testing at(key) *******/
			insertRandomInt(map1.at(keyVector[0]));
			cout << map1.at(keyVector[0]) << '\n';

			insertRandomInt(map1.at(keyVector[keyVectorSize / 4]));
			cout << map1.at(keyVector[keyVectorSize / 4]) << '\n';

			try {

				map1.at(keyVectorSize);

			}
			catch (std::out_of_range&) {

				cout << "at exception caught\n";

			}

			cout << map2.at(keyVector[0]) << '\n';

			try {

				map2.at(keyVectorSize);

			}
			catch (std::out_of_range&) {

				cout << "const at exception caught\n";

			}

			/******* testing find(key) *******/
			Iter tmpIter = map1.find(keyVector[0]);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);
			printPairFunPtr(*tmpIter);

			tmpIter = map1.find(keyVector[keyVectorSize / 4]);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);
			printPairFunPtr(*tmpIter);

			tmpIter = map1.find(keyVectorSize);
			cout << (tmpIter == map1.end()) << '\n';

			cIter = map2.find(keyVector[keyVectorSize / 3]);
			printPairFunPtr(*cIter);

			cIter = map2.find(keyVectorSize);
			cout << (cIter == map2.end()) << '\n';

			/******* testing clear() *******/
			Map map5(doubleIntPairVec.begin(), doubleIntPairVec.begin() + 10);
			cout << map5.size() << " " << map5.empty() << '\n';
			for_each(map5.begin(), map5.end(), printPairFunPtr);
			for_each(map5.rbegin(), map5.rend(), printPairFunPtr);

			map5.clear();
			cout << map5.size() << " " << map5.empty() << '\n';
			for_each(map5.begin(), map5.end(), printPairFunPtr);
			for_each(map5.rbegin(), map5.rend(), printPairFunPtr);
			
			/******* testing lower_bound *******/
			tmpIter = map1.lower_bound(map1.begin()->first);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.lower_bound(keyVector[keyVectorSize / 4]);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.lower_bound(-10);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.lower_bound(keyVectorSize);
			if (tmpIter == map1.end())
				cout << "lower_bound map1 end\n";

			cIter = map2.lower_bound(map2.begin()->first);
			printPairFunPtr(*cIter);

			cIter = map2.lower_bound(-10);
			printPairFunPtr(*cIter);

			cIter = map2.lower_bound(keyVectorSize);
			if (cIter == map2.end())
				cout << "lower_bound map2 end\n";
			
			/******* testing upper_bound *******/
			tmpIter = map1.upper_bound(map1.begin()->first);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.upper_bound(keyVector[keyVectorSize / 4]);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.upper_bound(-10);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.upper_bound(keyVectorSize);
			if (tmpIter == map1.end())
				cout << "upper_bound map1 end\n";

			tmpIter = map1.upper_bound( keyVector[ keyVectorSize - 1] );
			if (tmpIter == map1.end())
				cout << "upper_bound map1 end\n";

			cIter = map2.upper_bound(map2.begin()->first);
			printPairFunPtr(*cIter);

			cIter = map2.upper_bound(-10);
			printPairFunPtr(*cIter);

			cIter = map2.upper_bound(keyVectorSize);
			if (cIter == map2.end())
				cout << "upper_bound map2 end\n";
			
			
			/******* testing equal_range *******/
			ft::pair<Iter, Iter> iterPair = map1.equal_range(
				map1.begin()->first);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);

			iterPair = map1.equal_range(keyVector[ keyVectorSize / 4]);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);

			iterPair = map1.equal_range(-10);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);

			iterPair = map1.equal_range(keyVectorSize);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);

			ft::pair< ConstIter, ConstIter > constIterPair;

			constIterPair = map2.equal_range(map2.begin()->first);
			for_each(constIterPair.first, constIterPair.second, printPairFunPtr);

			constIterPair = map2.equal_range(keyVector[ keyVectorSize / 4]);
			for_each(constIterPair.first, constIterPair.second, printPairFunPtr);

			constIterPair = map2.equal_range(-10);
			for_each(constIterPair.first, constIterPair.second, printPairFunPtr);

			constIterPair = map2.equal_range(keyVectorSize);
			for_each(constIterPair.first, constIterPair.second, printPairFunPtr);

			/******* testing erase(pos) *******/
			map4.erase(map4.begin());

			map4.erase( --Iter(map4.end()) );

			/******* testing erase(first, last) *******/
			// gets the element that is "keyVectorSize / 10" away from
				// beginning so that "keyVectorSize / 10" elements
				// get erased
			tmpIter = map4.find(keyVector[ keyVectorSize / 10 ] );
			map4.erase(map4.begin(), tmpIter);

			map4.erase(map4.begin(), map4.begin());

			map4.erase(map4.end(), map4.end());

			/******* testing erase(key) *******/
			cout << map1.erase(keyVector[0]) << '\n'; 
			cout << map1.erase(keyVector[ keyVectorSize / 2 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 3 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 4 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 5 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 6 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 7 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 8 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 9 ]) << '\n';
			cout << map1.erase(keyVector[ keyVectorSize / 10 ]) << '\n';

			cout << map1.erase(keyVectorSize) << '\n';
			cout << map1.erase(keyVectorSize + 1) << '\n';
			cout << map1.erase(keyVectorSize + 2) << '\n';
			cout << map1.erase(keyVectorSize + 3) << '\n';
			cout << map1.erase(keyVectorSize + 4) << '\n';
			cout << map1.erase(keyVectorSize + 5) << '\n';
			
			/******* testing relational operators *******/
			map5 = map3;
			map5[keyVectorSize / 4] = map3[keyVectorSize / 4] - 1;

			cout << (map1 == map2) << '\n';
			cout << (map1 == map3) << '\n';
			cout << (map1 == map4) << '\n';
			cout << (map1 == map5) << '\n';
			cout << (map2 == map3) << '\n';
			cout << (map2 == map4) << '\n';
			cout << (map2 == map5) << '\n';
			cout << (map3 == map4) << '\n';
			cout << (map3 == map5) << '\n';
			cout << (map4 == map5) << '\n';

			cout << (map1 != map2) << '\n';
			cout << (map1 != map3) << '\n';
			cout << (map1 != map4) << '\n';
			cout << (map1 != map5) << '\n';
			cout << (map2 != map3) << '\n';
			cout << (map2 != map4) << '\n';
			cout << (map2 != map5) << '\n';
			cout << (map3 != map4) << '\n';
			cout << (map3 != map5) << '\n';
			cout << (map4 != map5) << '\n';

			cout << (map1 < map2) << '\n';
			cout << (map1 < map3) << '\n';
			cout << (map1 < map4) << '\n';
			cout << (map1 < map5) << '\n';
			cout << (map2 < map3) << '\n';
			cout << (map2 < map4) << '\n';
			cout << (map2 < map5) << '\n';
			cout << (map3 < map4) << '\n';
			cout << (map3 < map5) << '\n';
			cout << (map4 < map5) << '\n';

			cout << (map1 <= map2) << '\n';
			cout << (map1 <= map3) << '\n';
			cout << (map1 <= map4) << '\n';
			cout << (map1 <= map5) << '\n';
			cout << (map2 <= map3) << '\n';
			cout << (map2 <= map4) << '\n';
			cout << (map2 <= map5) << '\n';
			cout << (map3 <= map4) << '\n';
			cout << (map3 <= map5) << '\n';
			cout << (map4 <= map5) << '\n';

			cout << (map1 > map2) << '\n';
			cout << (map1 > map3) << '\n';
			cout << (map1 > map4) << '\n';
			cout << (map1 > map5) << '\n';
			cout << (map2 > map3) << '\n';
			cout << (map2 > map4) << '\n';
			cout << (map2 > map5) << '\n';
			cout << (map3 > map4) << '\n';
			cout << (map3 > map5) << '\n';
			cout << (map4 > map5) << '\n';

			cout << (map1 >= map2) << '\n';
			cout << (map1 >= map3) << '\n';
			cout << (map1 >= map4) << '\n';
			cout << (map1 >= map5) << '\n';
			cout << (map2 >= map3) << '\n';
			cout << (map2 >= map4) << '\n';
			cout << (map2 >= map5) << '\n';
			cout << (map3 >= map4) << '\n';
			cout << (map3 >= map5) << '\n';
			cout << (map4 >= map5) << '\n';

			/******* testing std::swap *******/
			std::swap(map1, map3);

			std::swap(map3, map4);

			std::swap(map4, map5);

			/******* printing map's elements *******/
			// in order
			for_each(map1.begin(), map1.end(), printPairFunPtr);
			for_each(map2.begin(), map2.end(), printPairFunPtr);
			for_each(map3.begin(), map3.end(), printPairFunPtr);
			for_each(map4.begin(), map4.end(), printPairFunPtr);
			for_each(map5.begin(), map5.end(), printPairFunPtr);

			// in reverse order
			for_each(map1.rbegin(), map1.rend(), printPairFunPtr);
			for_each(map2.rbegin(), map2.rend(), printPairFunPtr);
			for_each(map3.rbegin(), map3.rend(), printPairFunPtr);
			for_each(map4.rbegin(), map4.rend(), printPairFunPtr);
			for_each(map5.rbegin(), map5.rend(), printPairFunPtr);

			/******* testing size and empty *******/
			cout << map1.size() << " " << map1.empty() << '\n';
			cout << map2.size() << " " << map2.empty() << '\n';
			cout << map3.size() << " " << map3.empty() << '\n';
			cout << map4.size() << " " << map4.empty() << '\n';
			cout << map5.size() << " " << map5.empty() << '\n';

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

			/******* testing operator[] *******/ 
			cout << map1[ keyVector[0] ] << '\n';
			insertRandomInt(map1[ keyVector[0] ] );
			cout << map1[ keyVector[0] ] << '\n';

			cout << map1[ keyVector[keyVectorSize / 2] ] << '\n';
			insertRandomInt(map1[ keyVector[keyVectorSize / 2] ]); 

			cout << map1[ keyVectorSize * 2 ] << '\n';
			insertRandomInt(map1[ keyVectorSize ]); 
			cout << map1[ keyVectorSize * 2 ] << '\n';

			/******* testing swap *******/ 
			map4.swap(map2);

			/******* testing iterators *******/ 
			Iter it1;

			Iter it2 = map1.begin();
			for_each(it2, ++Iter(it2), printPairFunPtr);

			cout << (it1 == it2) << '\n';
			cout << (it1 != it2) << '\n';

			it2->second = 10;
			for_each(it2, ++Iter(it2), printPairFunPtr);

			cout << (it1 == it2) << '\n';
			cout << (it1 != it2) << '\n';

			it1 = it2++;
			for_each(it1, ++Iter(it1), printPairFunPtr);
			for_each(it2, ++Iter(it2), printPairFunPtr);

			cout << (it1 == it2) << '\n';
			cout << (it1 != it2) << '\n';

			cout << it2->second << (++it2)->second << '\n';

			++it2 = map3.begin();

			cout << (it1 == it2) << '\n';
			cout << (it1 != it2) << '\n';

			ConstIter constIt(it2);
			for_each(constIt, ++ConstIter(constIt), printPairFunPtr);

			cout << (constIt == it1) << '\n';
			cout << (constIt == it2) << '\n';
			cout << (constIt != it1) << '\n';
			cout << (constIt != it2) << '\n';

			constIt = it1++;
			for_each(constIt, ++ConstIter(constIt), printPairFunPtr);
			for_each(it1, ++Iter(it1), printPairFunPtr);

			cout << (it1 == constIt) << '\n';
			cout << (it1 != constIt) << '\n';

			--it1 = it2;
			for_each(constIt, ++ConstIter(constIt), printPairFunPtr);

			cout << (it1 == it2) << '\n';
			cout << (it1 != it2) << '\n';

			const Iter constNormalIt(map2.begin());

			constIt = map2.end();

			--constIt;

			cout << constIt->first << constIt->second << '\n';

			it1 = constNormalIt;

			cout << (constNormalIt == it1) << '\n';
			cout << (it1 == constNormalIt) << '\n';
			cout << (constNormalIt != it1) << '\n';
			cout << (it1 != constNormalIt) << '\n';

			RevIter rit(map3.rend());

			--rit;

			insertRandomInt(rit->second);
			for_each(rit, ++RevIter(rit), printPairFunPtr);

			cout << (*rit).first << (*rit).second << '\n';

			ConstRevIter constRit(rit);
			for_each(constRit, ++ConstRevIter(constRit), printPairFunPtr);

			cout << (constRit == rit) << '\n';
			cout << (constRit != rit) << '\n';

			/******* testing count *******/
			cout << map1.count(map1.begin()->first) << '\n';
			cout << map1.count( (--map1.end())->first ) << '\n';
			cout << map1.count(keyVector[ keyVectorSize / 2] ) << '\n';
			cout << map1.count(keyVectorSize) << '\n';
			cout << map1.count(keyVectorSize + 1) << '\n';
			cout << map1.count(keyVectorSize + 2) << '\n';
			cout << map1.count(keyVectorSize + 3) << '\n';
			cout << map1.count(keyVectorSize + 4) << '\n';
			cout << map1.count(keyVectorSize + 5) << '\n';
			
			/******* testing lower_bound *******/
			Iter tmpIter = map1.lower_bound(map1.begin()->first);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.lower_bound(keyVector[keyVectorSize / 4]);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.lower_bound(-10);
			if (tmpIter == map1.end())
				cout << "lower_bound map1 end\n";

			tmpIter = map1.lower_bound(keyVectorSize);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);
			
			/******* testing upper_bound *******/
			tmpIter = map1.upper_bound(map1.begin()->first);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.upper_bound(keyVector[keyVectorSize / 4]);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.upper_bound(-10);
			if (tmpIter == map1.end())
				cout << "upper_bound map1 end\n";

			tmpIter = map1.upper_bound(keyVectorSize);
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);

			tmpIter = map1.upper_bound( keyVector[ keyVectorSize - 1] );
			printPairFunPtr(*tmpIter);
			insertRandomInt(tmpIter->second);
			
			/******* testing equal_range *******/
			ft::pair<Iter, Iter> iterPair = map1.equal_range(
				map1.begin()->first);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);

			iterPair = map1.equal_range(keyVector[ keyVectorSize / 4]);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);

			iterPair = map1.equal_range(-10);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);

			iterPair = map1.equal_range(keyVectorSize);
			for_each(iterPair.first, iterPair.second, printPairFunPtr);
			printPairFunPtr( *(iterPair.first) );

			/******* printing map's elements *******/
			// in order
			for_each(map1.begin(), map1.end(), printPairFunPtr);
			for_each(map2.begin(), map2.end(), printPairFunPtr);
			for_each(map3.begin(), map3.end(), printPairFunPtr);
			for_each(map4.begin(), map4.end(), printPairFunPtr);

			// in reverse order
			for_each(map1.rbegin(), map1.rend(), printPairFunPtr);
			for_each(map2.rbegin(), map2.rend(), printPairFunPtr);
			for_each(map3.rbegin(), map3.rend(), printPairFunPtr);
			for_each(map4.rbegin(), map4.rend(), printPairFunPtr);

			/******* testing size and empty *******/
			cout << map1.size() << " " << map1.empty() << '\n';
			cout << map2.size() << " " << map2.empty() << '\n';
			cout << map3.size() << " " << map3.empty() << '\n';
			cout << map4.size() << " " << map4.empty() << '\n';

			/******* testing max_size() *******/
			cout << (map1.max_size() == map2.max_size()) << '\n';
			Map::size_type upperLimit =
				std::numeric_limits<Map::difference_type>::max();
			cout << (map1.max_size() <= upperLimit) << '\n';

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

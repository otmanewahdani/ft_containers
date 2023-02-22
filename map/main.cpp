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

static void insertRandomInt(int& a){ a = std::rand() % 100000; }

using std::string;
using std::cout;
using std::less;
using std::greater;
using std::vector;

int main(){

	std::time_t start = std::time(NULL);

	runPairtests();

	/******* types used in tests *******/
	// comparison objects types
	typedef less<int> Less;
	typedef greater<int> Greater;

	// making a keyVectorSize amount of unique int keys
	const int keyVectorSize = 1000000;
	vector<int> keyVector;
	keyVector.reserve(keyVectorSize);
	for (int i = 0; i < keyVectorSize; ++i)
		keyVector.push_back(i);
	std::random_shuffle(keyVector.begin(), keyVector.end());
	
	// making a randomIntsVecSize amount of random ints
	const int randomIntsVecSize = 1000000;
	vector<int> randomIntsVec(randomIntsVecSize);
	std::for_each(randomIntsVec.begin(), randomIntsVec.end(),
		insertRandomInt);

	// testing map with value_type of pair<int, int>
	{
		/******* types used in tests *******/
		// map::value_type aka pair
		typedef ft::pair<const int, int> PairVal;

		// comparator
		typedef greater<int> Greater;
		typedef less<int> Less;

		// allocator type
		typedef std::allocator< PairVal > Allocator;

		// making a vector of a keyVectorSize amount of
			// ft::pair<int, int> elements
		vector< ft::pair<int, int> > doubleIntPairVec;
		doubleIntPairVec.reserve(keyVectorSize);
		for (size_t i = 0; i < keyVector.size(); ++i)
			doubleIntPairVec[i] = 
				ft::make_pair(keyVector[i], randomIntsVec[i]);

		// testing with comparator of type std::less
		{

			/******* types used in tests *******/
			// map type
			typedef ft::map<int, int> Map;

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
				Map Map1(Less());
				Map Map2(Less(), Allocator());
			}

			Map Map1;

			InsertPair insertRet;
			for (size_t i = 0; i < doubleIntPairVec.size(); ++i){

				insertRet = Map1.insert(doubleIntPairVec[i]);
				cout << insertRet.first->first << " " << 
					insertRet.first->second << " " << insertRet.second << '\n';

			}

			cout << '\n';

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
				Map Map1(Greater());
				Map Map2(Greater(), Allocator());
			}

			Map Map1;

			InsertPair insertRet;
			for (size_t i = 0; i < doubleIntPairVec.size(); ++i){

				insertRet = Map1.insert(doubleIntPairVec[i]);
				cout << insertRet.first->first << " " << 
					insertRet.first->second << " " << insertRet.second << '\n';

			}

			cout << '\n';

		} // end of testing with comparator of type std::greater

	} // end of testing map with value_type of pair<int, int>

	// testing map with value_type of pair<int, string>

	std::fstream executionTime("map execution time",
		std::fstream::app | std::fstream::out);

	std::time_t end = std::time(NULL);

	executionTime << "ft::map run time: " << double(end) - start
		<< " seconds\n";
	
	executionTime.close();

	return 0;

}

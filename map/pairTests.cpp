/* this file contains tests of ft::pair and ft::make_pair.
	these two components are reimplementations of their STL counterpart
	, therefore they are supposed to have similar behaviors */

#include <pairTests.hpp>

void runPairtests(){

	using std::string;
	using std::cout;

	ft::pair<int, string> pair1;

	cout << pair1.first << " " << pair1.second << '\n';

	ft::pair<int, string> pair2(10, "ten");

	cout << pair2.first << " " << pair2.second << '\n';
	
	cout << (pair1 == pair2) << '\n';
	cout << (pair1 != pair2) << '\n';
	cout << (pair1 < pair2) << '\n';
	cout << (pair1 <= pair2) << '\n';
	cout << (pair1 > pair2) << '\n';
	cout << (pair1 >= pair2) << '\n';

	pair1 = pair2;
	cout << (pair1 == pair2) << '\n';
	cout << (pair1 != pair2) << '\n';
	cout << (pair1 < pair2) << '\n';
	cout << (pair1 <= pair2) << '\n';
	cout << (pair1 > pair2) << '\n';
	cout << (pair1 >= pair2) << '\n';

	ft::pair<char, string> pair3(pair2);

	cout << static_cast<int>(pair3.first) << " " << pair3.second << '\n';

	// changed it from "ten" to "Ten. so it became lexicographically less
	pair1.second = "Ten";
	cout << (pair1 == pair2) << '\n';
	cout << (pair1 != pair2) << '\n';
	cout << (pair1 < pair2) << '\n';
	cout << (pair1 <= pair2) << '\n';
	cout << (pair1 > pair2) << '\n';
	cout << (pair1 >= pair2) << '\n';

	ft::pair<long, double> pair4 = ft::make_pair(10, 'a');

	cout << pair4.first << " " << pair4.second << '\n';

	ft::pair<char, string> pair5 = ft::make_pair(97.45, "true");

	cout << pair5.first << " " << pair5.second << '\n';

}

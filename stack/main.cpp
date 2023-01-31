/* this file contains tests of the ft::stack container class.
	these tests are meant to produce the same output as std::stack
	in order to demonstrate that ft::stack is a re-implementation of 
	its STL counterpart */

#include <stack.hpp>
#include <stack>
#include <list>
#include <deque>
#include <vector>

int main() {

	ft::stack<int> intStack1;

	(void) intStack1;

	return 0;

}

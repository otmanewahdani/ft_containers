#include <vector.hpp>
#include <iterator.hpp>
#include <iostream>
#include <vector>

int main(){

	ft::vector<int>::iterator::pointer i = new int[3];
	i[0] = 0;
	i[1] = 1;
	i[2] = 2;
	
	ft::vector<int>::iterator it(i);
	ft::vector<int>::const_iterator cit(i + 2);


	std::cout << it - cit << '\n';
	std::cout << cit - it << '\n';

	return 0;

}

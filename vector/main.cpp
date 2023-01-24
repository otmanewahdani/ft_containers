#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector.hpp>
#include <iterator.hpp>


int print = 0;

struct A{
	A(){ i = new int;}
	A(int i) { this->i = new int(i); /*if (print) std::cout << "int constructor called\n";*/}
	~A() { if (print) std::cout << *i << " destructor called\n"; delete i;}
	A(const A&a) { this->i = new int(*(a.i)); if (print) std::cout << *i << " copy constructor\n";}
	A& operator=(const A& a){ *i = *(a.i); if (print) std::cout << *i << " copy assign called\n"; return *this;}
	int *i;
	operator int() const { return *i; }
};


int main(){


	typedef ft::vector<A> Avec;
	//typedef ft::vector<int> Ivec;
	//typedef ft::vector<std::string> Svec;
	
	A arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
		14, 15, 16, 17, 18, 19, 20};

	Avec vec(arr, arr + 14);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 5, 109, 35);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 5, arr, arr);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 10, arr, arr + 12);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.end(), arr + 5, arr + 18);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.end(), 13804, 123);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 4, arr, arr + 20);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';


	std::istringstream str("12 5 47 734 747 47 7474 445 54 5445 544\
	544554 545 5 55 5 5 5 5 5 5 5 5 5 5 5 5 5    555   5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 89 ");
	std::istream_iterator<int> it(str);
	vec.insert(vec.begin() + 10, it, std::istream_iterator<int>());
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::const_iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	return 0;

}

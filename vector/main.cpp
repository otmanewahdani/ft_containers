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
	
	A arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

	Avec vec(arr, arr + 14);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 5, 109, 35);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 5, 0, 199);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 10, 32334, 7834);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 1029, 100, 123);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.begin() + 4, 78, 123);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	vec.insert(vec.end(), 13804, 123);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';


	/*std::istringstream str("12 5 47 734 747 47 7474 445 54 5445 544\
	544554 545 5 55 5 5 5 5 5 5 5 5 5 5 5 5 5    555   5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 ");
	std::istream_iterator<int> it(str);
	const Avec vec3(it, std::istream_iterator<int>());
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << '\n' << '\n';
	for (Avec::const_iterator it = vec3.begin(); it != vec3.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';*/

	return 0;

}

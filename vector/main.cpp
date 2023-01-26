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

	Avec vec(arr + 1, arr + 20);
	std::cout << "size: " << vec.size()  << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	Avec vec1(arr + 4, arr + 10);

	Avec vec2(vec);

	std::cout << (vec == vec1) << '\n';
	std::cout << (vec == vec2) << '\n';
	std::cout << (vec1 == vec2) << '\n';

	std::cout << (vec != vec1) << '\n';
	std::cout << (vec != vec2) << '\n';
	std::cout << (vec1 != vec2) << '\n';

	std::cout << (vec < vec1) << '\n';
	std::cout << (vec < vec2) << '\n';
	std::cout << (vec1 < vec2) << '\n';

	std::cout << (vec <= vec1) << '\n';
	std::cout << (vec <= vec2) << '\n';
	std::cout << (vec1 <= vec2) << '\n';

	std::cout << (vec > vec1) << '\n';
	std::cout << (vec > vec2) << '\n';
	std::cout << (vec1 > vec2) << '\n';

	std::cout << (vec >= vec1) << '\n';
	std::cout << (vec >= vec2) << '\n';
	std::cout << (vec1 >= vec2) << '\n';

	return 0;

}

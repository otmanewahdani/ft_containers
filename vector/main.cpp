#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector.hpp>
#include <iterator.hpp>


int print = 1;

struct A{
	A(){ i = new int;}
	A(int i) { this->i = new int(i); /*if (print) std::cout << "int constructor called\n";*/}
	~A() { delete i; if (print) std::cout << "destructor called\n";}
	A(const A&a) { this->i = new int(*(a.i)); if (print) std::cout << "copy constructor\n";}
	A& operator=(const A& a){ *i = *(a.i); if (print) std::cout << " copy assign called\n"; return *this;}
	int *i;
};


int main(){


	A arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

	ft::vector<A> vec(arr, arr + 14);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';

	ft::vector<A> vec1(vec);
	std::cout << "size: " << vec1.size() << ", capacity: " << vec1.capacity() << '\n' << '\n';

	ft::vector<A> vec2(10000, arr[0]);
	std::cout << "size: " << vec2.size() << ", capacity: " << vec2.capacity() << '\n' << '\n';

	std::istringstream str("12 5 47 734 747 47 7474 445 54 5445 544\
	544554 545 5 55 5 5 5 5 5 5 5 5 5 5 5 5 5    555   5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 ");
	std::istream_iterator<int> it(str);
	ft::vector<A> vec3(it, std::istream_iterator<int>());
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << '\n' << '\n';
	
	return 0;

}

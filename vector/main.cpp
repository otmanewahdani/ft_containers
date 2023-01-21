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
	~A() { delete i; if (print) std::cout << "destructor called\n";}
	A(const A&a) { this->i = new int(*(a.i)); if (print) std::cout << "copy constructor\n";}
	A& operator=(const A& a){ *i = *(a.i); if (print) std::cout << " copy assign called\n"; return *this;}
	int *i;
	operator int() const { return *i; }
};


int main(){


	typedef ft::vector<A> Avec;
	/*typedef ft::vector<int> Ivec;
	typedef ft::vector<std::string> Svec;*/
	
	A arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

	Avec vec(arr, arr + 14);
	std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';
	for (Avec::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	Avec vec1(vec.begin(), vec.end());
	std::cout << "size: " << vec1.size() << ", capacity: " << vec1.capacity() << '\n' << '\n';
	for (Avec::reverse_iterator it = vec1.rbegin(); it != vec1.rend(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';



	std::istringstream str("12 5 47 734 747 47 7474 445 54 5445 544\
	544554 545 5 55 5 5 5 5 5 5 5 5 5 5 5 5 5    555   5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 ");
	std::istream_iterator<int> it(str);
	const Avec vec3(it, std::istream_iterator<int>());
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << '\n' << '\n';
	for (Avec::const_iterator it = vec3.begin(); it != vec3.end(); it++)
		std::cout << *it << '\n';
	std::cout << '\n';

	const Avec vec4(1028000, arr[6]);
	std::cout << "size: " << vec4.size() << ", capacity: " << vec4.capacity() << '\n' << '\n';
	for (Avec::const_reverse_iterator it = vec4.rbegin(); it != vec4.rend(); it++)
		std::cout << *it << '\n';

	*(vec.begin() + 5) = 1024;
	std::cout << vec.at(5) << '\n';
	vec.front() = 10;
	std::cout << (*vec.begin() == vec.front()) << '\n';
	vec.back() = 23;
	std::cout << (*(vec.end() - 1) == vec.back()) << '\n';

	std::cout << (*vec4.begin() == vec4.front()) << '\n';
	std::cout << (*(vec4.end() - 1) == vec4.back()) << '\n';
	std::cout << (*(vec4.begin() + 3677) == vec4[3677]) << '\n';

	return 0;

}

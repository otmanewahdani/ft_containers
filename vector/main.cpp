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
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec.at(i) << '\n';
	std::cout << '\n';

	Avec vec1(vec);
	std::cout << "size: " << vec1.size() << ", capacity: " << vec1.capacity() << '\n' << '\n';
	for (size_t i = 0; i < vec1.size(); i++)
		std::cout << vec1[i] << '\n';
	std::cout << '\n';



	std::istringstream str("12 5 47 734 747 47 7474 445 54 5445 544\
	544554 545 5 55 5 5 5 5 5 5 5 5 5 5 5 5 5    555   5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 ");
	std::istream_iterator<int> it(str);
	Avec vec3(it, std::istream_iterator<int>());
	std::cout << "size: " << vec3.size() << ", capacity: " << vec3.capacity() << '\n' << '\n';
	for (size_t i = 0; i < vec3.size(); i++)
		std::cout << vec3[i] << '\n';
	std::cout << '\n';

	Avec vec2(10000, arr[0]);
	vec2 = vec3;
	std::cout << "size: " << vec2.size() << ", capacity: " << vec2.capacity() << '\n' << '\n';
	for (size_t i = 0; i < vec2.size(); i++)
		std::cout << vec2[i] << '\n';
	std::cout << '\n';


	const Avec vec4(10200, arr[6]);
	std::cout << "size: " << vec4.size() << ", capacity: " << vec4.capacity() << '\n' << '\n';
	for (size_t i = 0; i < vec4.size(); i++)
		std::cout << vec4.at(i) << '\n';
	std::cout << '\n';
	for (size_t i = 0; i < vec4.size(); i++)
		std::cout << vec4[i] << '\n';
	std::cout << '\n';

	vec[5] = 1024;
	std::cout << vec.at(5) << '\n';
	vec.front() = 10;
	std::cout << (vec[0] == vec.front()) << '\n';
	vec.back() = 23;
	std::cout << (vec[vec.size() - 1] == vec.back()) << '\n';

	std::cout << (vec4[0] == vec4.front()) << '\n';
	std::cout << (vec4[vec.size() - 1] == vec4.back()) << '\n';
	std::cout << (vec4.at(1) == vec4[1]) << '\n';

	try {
		std::cout << vec.at(14) << '\n';
	}
	catch (std::out_of_range& error){
		std::cout << "exception" << '\n';
	}

	return 0;

}

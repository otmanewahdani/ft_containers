#include <vector>
#include <iostream>
#include <cstdlib>
#include <vector.hpp>
#include <iterator.hpp>


int print = 0;

struct A{
	A(){ i = new int;}
	A(int i) { this->i = new int(i); if (print) std::cout << "int constructor called\n";}
	~A() { delete i; if (print) std::cout << "destructor called\n";}
	A(const A&a) { this->i = new int(*(a.i)); if (print) std::cout << "copy constructor\n";}
	A& operator=(const A& a){ *i = *(a.i); if (print) std::cout << " copy assign called\n"; return *this;}
	int *i;
};


int main(){

	ft::vector<A> vec;
	A a(10);

	/*for (int i = 0; i < 10000; i++){

		vec.push_back(a);
		std::cout << "size: " << vec.size() << ", capacity: " << vec.capacity() << '\n' << '\n';

	}*/
	
	return 0;

}

#include <vector>
#include <iostream>
#include <vector.hpp>
#include <iterator.hpp>


struct A{
	A(){ i = new int;}
	A(int i) { this->i = new int(i); std::cout << "constructor called\n";}
	~A() { delete i; std::cout << "destructor called\n";}
	A(const A&a) { this->i = new int(*(a.i)); std::cout << "copy constructor\n";}
	A& operator=(const A& a){ *i = *(a.i); std::cout << " copy assign called\n"; return *this;}
	int *i;
};


int main(){

	ft::vector<A> vec;

	A* a = new A;
	vec.assign(3 , *a);
	std::cout << '\n';
	vec.assign(4, *a);
	std::cout << '\n';

	return 0;

}

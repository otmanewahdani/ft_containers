#include <vector>
#include <iostream>
#include <cstdlib>
#include <vector.hpp>
#include <iterator.hpp>


struct A{
	A(){ i = new int;}
	A(int i) { this->i = new int(i); std::cout << "int constructor called\n";}
	~A() { delete i; std::cout << "destructor called\n";}
	A(const A&a) { this->i = new int(*(a.i)); std::cout << "copy constructor\n";}
	A& operator=(const A& a){ *i = *(a.i); std::cout << " copy assign called\n"; return *this;}
	int *i;
};


int main(){

	ft::vector<A> *vec = new ft::vector<A>;

	A* a = new A(4);
	vec->assign(10 , *a);
	std::cout << '\n';
	vec->assign(100000, *a);
	std::cout << '\n';

	delete vec;
	delete a;

	return 0;

}

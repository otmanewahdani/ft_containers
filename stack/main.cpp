/* this file contains tests of the ft::stack container class.
	these tests are meant to produce the same output as std::stack
	in order to demonstrate that ft::stack is a re-implementation of 
	its STL counterpart */

#include <stack.hpp>
#include <stack>
#include <list>
#include <deque>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout;
using std::string;
using std::list;
using std::deque;

static void insertRandomInt(int& a){ a = std::rand() % 100000; }

static void insertRandomString(string& str) {

	static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

	const int len = rand() % 200;
	str.reserve(len);

    for (int i = 0; i < len; ++i)
		str += alphanum[rand() % (sizeof(alphanum) - 1)];

}

int main() {

	std::time_t start = std::time(NULL);

	typedef ft::stack< int, ft::vector<int> > IntStack;
	typedef ft::stack< string, ft::vector<string> > StringStack;

	std::srand(1337);
	
	// testing stack<int>
	const int intVecSize = 1000000;
	ft::vector<int> intVec(intVecSize);
	std::for_each(intVec.begin(), intVec.end(), insertRandomInt);

	IntStack intStack1;
	IntStack intStack2(intVec);
	IntStack intStack3(intStack2);

	cout << intStack1.empty() << " " << intStack1.size() << '\n';
	cout << intStack2.empty() << " " << intStack2.size() << '\n';
	cout << intStack3.empty() << " " << intStack3.size() << '\n';

	intStack1.push(rand() % 1000);
	cout << intStack1.empty() << " " << intStack1.size() << '\n';
	cout << intStack1.top() << '\n';
	intStack1.top() = 1337;
	cout << intStack1.top() << '\n';

	const IntStack constIntStack(intStack1);
	cout << constIntStack.empty() << " "
		<< constIntStack.size() << '\n';
	cout << constIntStack.top() << '\n';

	intStack1 = intStack3;
	cout << intStack1.empty() << " " << intStack1.size() << '\n';
	cout << intStack1.top() << '\n';

	while (intStack1.size() > intVecSize / 2)
		intStack1.pop();
	
	while (intStack2.size() > intVecSize / 3){
		intStack2.pop();
		intStack3.pop();
	}

	cout << (intStack1 == constIntStack) << '\n';
	cout << (intStack1 == intStack2) << '\n';
	cout << (intStack1 == intStack3) << '\n';
	cout << (constIntStack == intStack2) << '\n';
	cout << (constIntStack == intStack3) << '\n';
	cout << (intStack2 == intStack3) << '\n';

	cout << (intStack1 != constIntStack) << '\n';
	cout << (intStack1 != intStack2) << '\n';
	cout << (intStack1 != intStack3) << '\n';
	cout << (constIntStack != intStack2) << '\n';
	cout << (constIntStack != intStack3) << '\n';
	cout << (intStack2 != intStack3) << '\n';

	cout << (intStack1 < constIntStack) << '\n';
	cout << (intStack1 < intStack2) << '\n';
	cout << (intStack1 < intStack3) << '\n';
	cout << (constIntStack < intStack2) << '\n';
	cout << (constIntStack < intStack3) << '\n';
	cout << (intStack2 < intStack3) << '\n';

	cout << (intStack1 <= constIntStack) << '\n';
	cout << (intStack1 <= intStack2) << '\n';
	cout << (intStack1 <= intStack3) << '\n';
	cout << (constIntStack <= intStack2) << '\n';
	cout << (constIntStack <= intStack3) << '\n';
	cout << (intStack2 <= intStack3) << '\n';

	cout << (intStack1 > constIntStack) << '\n';
	cout << (intStack1 > intStack2) << '\n';
	cout << (intStack1 > intStack3) << '\n';
	cout << (constIntStack > intStack2) << '\n';
	cout << (constIntStack > intStack3) << '\n';
	cout << (intStack2 > intStack3) << '\n';

	cout << (intStack1 >= constIntStack) << '\n';
	cout << (intStack1 >= intStack2) << '\n';
	cout << (intStack1 >= intStack3) << '\n';
	cout << (constIntStack >= intStack2) << '\n';
	cout << (constIntStack >= intStack3) << '\n';
	cout << (intStack2 >= intStack3) << '\n';
	
	while (!intStack1.empty()){
		cout << intStack1.top() << '\n';
		intStack1.pop();
	}
	
	while (!intStack2.empty()){
		cout << intStack2.top() << '\n';
		intStack2.pop();
	}
	
	while (!intStack3.empty()){
		cout << intStack3.top() << '\n';
		intStack3.pop();
	}

	// testing stack<string>
	const int stringVecSize = 1000000;
	ft::vector<string> stringVec(stringVecSize);
	std::for_each(stringVec.begin(), stringVec.end(),
		insertRandomString);

	StringStack stringStack1(stringVec);
	StringStack stringStack2(stringStack1);
	StringStack stringStack3;

	stringStack3.push("1337");

	insertRandomString(stringStack1.top());
	insertRandomString(stringStack2.top());

	cout << stringStack1.top() << '\n';
	cout << stringStack2.top() << '\n';

	cout << stringStack1.size() << " " << stringStack1.empty() << '\n';
	cout << stringStack2.size() << " " << stringStack2.empty() << '\n';
	cout << stringStack3.size() << " " << stringStack3.empty() << '\n';

	stringStack3 = stringStack1;

	while (stringStack2.size() > stringVecSize - stringVecSize / 4)
		stringStack2.pop();
	
	cout << (stringStack1 == stringStack2) << '\n';
	cout << (stringStack1 == stringStack3) << '\n';
	cout << (stringStack2 == stringStack3) << '\n';
	
	cout << (stringStack1 != stringStack2) << '\n';
	cout << (stringStack1 != stringStack3) << '\n';
	cout << (stringStack2 != stringStack3) << '\n';
	
	cout << (stringStack1 < stringStack2) << '\n';
	cout << (stringStack1 < stringStack3) << '\n';
	cout << (stringStack2 < stringStack3) << '\n';
	
	cout << (stringStack1 <= stringStack2) << '\n';
	cout << (stringStack1 <= stringStack3) << '\n';
	cout << (stringStack2 <= stringStack3) << '\n';
	
	cout << (stringStack1 > stringStack2) << '\n';
	cout << (stringStack1 > stringStack3) << '\n';
	cout << (stringStack2 > stringStack3) << '\n';
	
	cout << (stringStack1 >= stringStack2) << '\n';
	cout << (stringStack1 >= stringStack3) << '\n';
	cout << (stringStack2 >= stringStack3) << '\n';
	
	while (!stringStack1.empty()){
		cout << stringStack1.top() << '\n';
		stringStack1.pop();
	}
	
	while (!stringStack2.empty()){
		cout << stringStack2.top() << '\n';
		stringStack2.pop();
	}
	
	while (!stringStack3.empty()){
		cout << stringStack3.top() << '\n';
		stringStack3.pop();
	}

	// testing stack with other containers
	{

		ft::stack<int, list<int> > listStack1;
		ft::stack<int, list<int> >
			listStack2(list<int>(intVec.begin(),
				intVec.begin() + intVec.size() / 4));

		cout << listStack1.size() << " " << listStack1.empty() << '\n';
		listStack1.push(1234);
		cout << listStack1.top() << '\n';
		cout << listStack1.size() << " " << listStack1.empty() << '\n';

		listStack1 = listStack2;
		cout << listStack1.size() << " " << listStack1.empty() << '\n';
		cout << listStack2.size() << " " << listStack2.empty() << '\n';

		cout << (listStack1 == listStack2) << '\n';
		cout << (listStack1 != listStack2) << '\n';
		cout << (listStack1 < listStack2) << '\n';
		cout << (listStack1 <= listStack2) << '\n';
		cout << (listStack1 > listStack2) << '\n';
		cout << (listStack1 >= listStack2) << '\n';
	
		insertRandomInt(listStack1.top());
		insertRandomInt(listStack2.top());

		listStack1.pop();
		listStack1.pop();
		listStack1.pop();
		listStack1.pop();

		listStack2.pop();

		while (!listStack2.empty()){
			cout << listStack2.top() << '\n';
			listStack2.pop();
		}

		while (!listStack1.empty()){
			cout << listStack1.top() << '\n';
			listStack1.pop();
		}

		ft::stack<int, deque<int> > dequeStack1(
			deque<int>(intVec.begin(),
				intVec.begin() + intVec.size() / 2));
		ft::stack<int, deque<int> > dequeStack2(dequeStack1);

		cout << (dequeStack1 == dequeStack1) << '\n';

		cout << dequeStack1.top() << '\n';
		cout << dequeStack2.top() << '\n';
		cout << dequeStack1.empty() << " " << dequeStack1.size() << '\n';
		cout << dequeStack2.empty() << " " << dequeStack2.size() << '\n';

		dequeStack1.top() = rand() % 10000;
		cout << dequeStack1.top() << '\n';
		dequeStack1.pop();

		dequeStack1.top() = rand() % 10000;
		cout << dequeStack1.top() << '\n';
		dequeStack1.pop();

		dequeStack1.top() = rand() % 10000;
		cout << dequeStack1.top() << '\n';
		dequeStack1.pop();

		dequeStack2.top() = rand() % 10000;
		cout << dequeStack1.top() << '\n';
		dequeStack1.pop();

		dequeStack2.top() = rand() % 10000;
		cout << dequeStack1.top() << '\n';
		dequeStack1.pop();

		cout << (dequeStack1 == dequeStack2) << '\n';
		cout << (dequeStack1 != dequeStack2) << '\n';
		cout << (dequeStack1 < dequeStack2) << '\n';
		cout << (dequeStack1 <= dequeStack2) << '\n';
		cout << (dequeStack1 > dequeStack2) << '\n';
		cout << (dequeStack1 >= dequeStack2) << '\n';

		dequeStack1.pop();
		dequeStack1.pop();

		dequeStack2.pop();
		dequeStack2.pop();
		dequeStack2.pop();

		while (!dequeStack2.empty()){
			cout << dequeStack2.top() << '\n';
			dequeStack2.pop();
		}

		while (!dequeStack1.empty()){
			cout << dequeStack1.top() << '\n';
			dequeStack1.pop();
		}

	}

	std::fstream executionTime("stack execution time",
		std::fstream::app | std::fstream::out);

	std::time_t end = std::time(NULL);

	executionTime << "ft::stack run time: " << double(end) - start
		<< " seconds\n";
	
	executionTime.close();

	
}

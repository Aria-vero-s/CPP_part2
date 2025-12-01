#include <iostream>
#include <vector>
#include <list>

#include "easyfind.hpp"

int main()
{
	std::vector<int> v;
	v.push_back(6);
	v.push_back(3);
	v.push_back(17);
	v.push_back(9);
	v.push_back(11);

	try {
		std::vector<int>::iterator it = easyfind(v, 17);
		std::cout << "Found in vector: " << *it << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	try {
		std::list<int>::iterator it2 = easyfind(l, 42);
		std::cout << "Found in list: " << *it2 << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "List test: " << e.what() << std::endl;
	}

	const std::vector<int> cv(v.begin(), v.end());
	try {
		std::vector<int>::const_iterator cit = easyfind(cv, 9);
		std::cout << "Found in const vector: " << *cit << std::endl;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

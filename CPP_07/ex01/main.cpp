#include <iostream>
#include <string>
#include "iter.hpp"

void printInt(const int &n) {
	std::cout << n << std::endl;
}

void increment(int &n) {
	n += 1;
}

template<typename T>
void printTemplate(const T &x) {
	std::cout << "Test " << x << std::endl;
}

int main()
{
	std::cout << ".............. test with int array .............." << std::endl;
	int arr[] = {0, 1, 2};
	unsigned int len = sizeof(arr) / sizeof(arr[0]);

	std::cout << "----- printInt -----" << std::endl;
	::iter(arr, len, printInt);

	std::cout << "----- printTemplate<int> -----" << std::endl;
	::iter(arr, len, printTemplate<int>);

	::iter(arr, len, increment);

	std::cout << "----- after increment: -----" << std::endl;
	::iter(arr, len, printInt);

	std::cout << "\n.............. test with std::string (const array) .............." << std::endl;
	const std::string sarr[] = {"chaine1", "chaine2", "chaine3"};
	unsigned int slen = sizeof(sarr) / sizeof(sarr[0]);

	::iter(sarr, slen, printTemplate<std::string>);

	std::cout << "\n----- test with char* array -----" << std::endl;
	const char* carr[] = { "one", "two", "three" };
	unsigned int clen = sizeof(carr) / sizeof(carr[0]);
	::iter(carr, clen, printTemplate<const char*>);

	return 0;
}
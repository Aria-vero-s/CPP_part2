#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
	try {
		// empty array
		Array<int> empty;
		std::cout << "empty size: " << empty.size() << std::endl;

		// array of ints
		Array<int> ai(5);
		for (unsigned int i = 0; i < ai.size(); ++i)
			ai[i] = static_cast<int>(i * 10);
		std::cout << "ai: ";
		for (unsigned int i = 0; i < ai.size(); ++i)
			std::cout << ai[i] << ' ';
		std::cout << std::endl;

		// copy constructor
		Array<int> copy = ai;
		copy[0] = 999;
		std::cout << "ai[0] = " << ai[0] << " (should be 0), copy[0] = " << copy[0] << std::endl;

		// assignment operator
		Array<int> assign;
		assign = ai;
		assign[1] = 888;
		std::cout << "ai[1] = " << ai[1] << " (should be 10), assign[1] = " << assign[1] << std::endl;

		// array of strings
		Array<std::string> as(3);
		as[0] = "chaine1";
		as[1] = "chaine2";
		as[2] = "chaine3";
		for (unsigned int i = 0; i < as.size(); ++i)
			std::cout << "as[" << i << "] = " << as[i] << std::endl;

		// out of range access -> should throw
		try {
			std::cout << "Accessing out-of-range element: ";
			std::cout << ai[10] << std::endl; // should throw
		} catch (std::exception & e) {
			std::cout << "caught exception: " << e.what() << std::endl;
		}

	} catch (std::exception & e) {
		std::cerr << "Uncaught exception: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

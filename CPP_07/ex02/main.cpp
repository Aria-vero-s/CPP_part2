#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
	try {
		Array<int> empty;
		std::cout << "empty size: " << empty.size() << std::endl;

		Array<int> ai(5);
		unsigned int i = 0;
		while (i < ai.size()) {
			ai[i] = static_cast<int>(i * 10);
			++i;
		}
		std::cout << "ai: ";
		i = 0;
		while (i < ai.size()) {
			std::cout << ai[i] << ' ';
			++i;
		}
		std::cout << std::endl;

		Array<int> copy = ai;
		copy[0] = 999;
		std::cout << "ai[0] = " << ai[0] << " (should be 0), copy[0] = " << copy[0] << std::endl;

		Array<int> assign;
		assign = ai;
		assign[1] = 888;
		std::cout << "ai[1] = " << ai[1] << " (should be 10), assign[1] = " << assign[1] << std::endl;

		Array<std::string> as(3);
		as[0] = "chaine1";
		as[1] = "chaine2";
		as[2] = "chaine3";
		i = 0;
		while (i < as.size()) {
			std::cout << "as[" << i << "] = " << as[i] << std::endl;
			++i;
		}
		try {
			std::cout << "Accessing out-of-range element: ";
			std::cout << ai[10] << std::endl;
		}
		catch (std::exception & e) {
			std::cout << "caught exception: " << e.what() << std::endl;
		}

	} catch (std::exception & e) {
		std::cerr << "Uncaught exception: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

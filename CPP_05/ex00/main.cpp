#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	try {
		Bureaucrat a("Alice", 2);
		std::cout << CYAN << a << std::endl << RESET;

		a.incrementGrade();
		std::cout << "After increment: " << a << std::endl;

		std::cout << "Try to increment past 1..." << std::endl;
		a.incrementGrade();
	}
	catch (std::exception& e) {
		std::cout << RED << "Exception caught: " << e.what() << std::endl << RESET;
	}

	try {
		Bureaucrat b("Bob", 151);
		std::cout << b << std::endl;
	}
	catch (std::exception& e) {
		std::cout << RED << "Exception caught during construction: " << e.what() << std::endl << RESET;
	}

	try {
		Bureaucrat c("Charlie", 149);
		std::cout << MAGENTA << c << std::endl << RESET;
		c.decrementGrade();
		std::cout << "After decrement: " << c << std::endl;
		c.decrementGrade();
	}
	catch (std::exception& e) {
		std::cout << RED << "Exception caught: " << e.what() << std::endl << RESET;
	}

	return 0;
}

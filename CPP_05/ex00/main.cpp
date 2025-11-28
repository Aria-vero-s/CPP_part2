#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	std::cout << BOLD << "----- TEST ------" << RESET << std::endl;
	std::cout << std::endl;
	try {
		Bureaucrat a("Alice", 2);
		std::cout << CYAN << a << std::endl << RESET;

		a.incrementGrade();
		std::cout << "After increment: " << a << std::endl;

		std::cout << "Try to increment past 1..." << std::endl;
		a.incrementGrade();
	}
	catch (std::exception& e) {
		std::cout << RED << "Exception caught: " << RESET << BOLD << e.what() << std::endl << RESET;
	}

	try {
		Bureaucrat b("Bob", 151);
		std::cout << b << std::endl;
	}
	catch (std::exception& e) {
		std::cout << RED << "Exception caught during construction: " << RESET << BOLD << e.what() << std::endl << RESET;
	}

	try {
		Bureaucrat c("Charlie", 149);
		std::cout << MAGENTA << c << std::endl << RESET;
		c.decrementGrade();
		std::cout << "After decrement: " << c << std::endl;
		c.decrementGrade();
	}
	catch (std::exception& e) {
		std::cout << RED << "Exception caught: " << RESET << BOLD << e.what() << std::endl << RESET;
	}
	std::cout << std::endl;
	std::cout << BOLD << "----- END TEST ------" << RESET << std::endl;
	return 0;
}

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
	std::cout << BOLD << "----- TEST ------" << RESET << std::endl;
	std::cout << std::endl;
	try {
		Bureaucrat alice("Alice", 5);
		Form contract("TopSecret", 10, 5);
		std::cout << CYAN << alice << RESET << std::endl;
		std::cout << MAGENTA << contract << RESET << std::endl;
		alice.signForm(contract);
		std::cout << MAGENTA << contract << RESET << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
	try {
		Bureaucrat bob("Bob", 42);
		Form report("Report", 20, 10);
		std::cout << YELLOW << bob << RESET << std::endl;
		std::cout << MAGENTA << report << RESET << std::endl;
		bob.signForm(report);
		std::cout << MAGENTA << report << RESET << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
	try {
		Form broken("Broken", 0, 10);
		(void)broken;
	}
	catch (std::exception &e) {
		std::cout << "Form construction exception: " << e.what() << std::endl;
	}
	std::cout << std::endl;
	std::cout << BOLD << "----- END TEST ------" << RESET << std::endl;
	return 0;
}

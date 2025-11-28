#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    try {
        Bureaucrat a("Alice", 2);
        std::cout << CYAN << a << std::endl << RESET; // Alice, bureaucrat grade 2

        a.incrementGrade(); // becomes 1
        std::cout << "After increment: " << a << std::endl;

        // This will throw (going above highest)
        std::cout << "Try to increment past 1..." << std::endl;
        a.incrementGrade(); // should throw GradeTooHighException
    }
    catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << std::endl << RESET;
    }

    try {
        // invalid construction -> too low
        Bureaucrat b("Bob", 151);
        std::cout << b << std::endl;
    }
    catch (std::exception& e) {
        std::cout << RED << "Exception caught during construction: " << e.what() << std::endl << RESET;
    }

    try {
        Bureaucrat c("Charlie", 149);
        std::cout << MAGENTA << c << std::endl << RESET;
        c.decrementGrade(); // becomes 150
        std::cout << "After decrement: " << c << std::endl;
        c.decrementGrade(); // becomes 151 -> throw
    }
    catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << std::endl << RESET;
    }

    return 0;
}

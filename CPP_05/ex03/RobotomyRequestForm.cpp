#include "RobotomyRequestForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequest", 72, 45), target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& t) : AForm("RobotomyRequest", 72, 45), target(t) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) : AForm(other), target(other.target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	if (this != &other)
		AForm::operator=(other);
	return *this;
}

void RobotomyRequestForm::executeAction() const {
	std::cout << BOLD << "***drilling noises***" << RESET << std::endl;
	int r = std::rand();
	if (r % 2 == 0)
		std::cout << GREEN << target << " has been robotomized successfully." << RESET << std::endl;
	else
		std::cout << RED << "The robotomy failed on " << target << "." << RESET << std::endl;
}

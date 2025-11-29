#include "PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardon", 25, 5), target("default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& t) : AForm("PresidentialPardon", 25, 5), target(t) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) : AForm(other), target(other.target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other) {
	if (this != &other)
		AForm::operator=(other);
	return *this;
}

void PresidentialPardonForm::executeAction() const {
	std::cout << CYAN << target << " has been pardoned by Zaphod Beeblebrox." << RESET << std::endl;
}

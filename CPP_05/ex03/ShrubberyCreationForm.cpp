#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreation", 145, 137), target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& t) : AForm("ShrubberyCreation", 145, 137), target(t) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : AForm(other), target(other.target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other)
		AForm::operator=(other);
	return *this;
}

void ShrubberyCreationForm::executeAction() const {
	std::cout << YELLOW << BOLD << target << "_shrubbery file created." << RESET << std::endl;
	std::ofstream f((target + "_shrubbery").c_str());
	if (!f) return;
	f << "ASCII trees\n";
}

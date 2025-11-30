#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

typedef AForm* (*FormCreator)(const std::string& target);

static AForm* createShrubbery(const std::string& target) {
	return new ShrubberyCreationForm(target);
}
static AForm* createRobotomy(const std::string& target) {
	return new RobotomyRequestForm(target);
}
static AForm* createPardon(const std::string& target) {
	return new PresidentialPardonForm(target);
}

Intern::Intern() {}

Intern::Intern(const Intern& other) {
	(void)other;
}

Intern::~Intern() {}

Intern& Intern::operator=(const Intern& other) {
	(void)other;
	return *this;
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
	const std::string names[] = {
		"shrubbery creation",
		"shrubbery",
		"robotomy request",
		"robotomy",
		"presidential pardon",
		"presidential"
	};

	const FormCreator creators[] = {
		createShrubbery,
		createShrubbery,
		createRobotomy,
		createRobotomy,
		createPardon,
		createPardon
	};

	const std::size_t count = sizeof(names) / sizeof(names[0]);
	std::size_t i = 0;

	while (i < count) {
		if (names[i] == formName) {
			AForm* form = creators[i](target);
			std::cout << "Intern creates " << formName << std::endl;
			return form;
		}
		++i;
	}

	std::cout << "Intern couldn't create \"" << formName << "\": unknown form name" << std::endl;
	return NULL;
}

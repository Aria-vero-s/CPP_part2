#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << std::endl;
	std::cout << BOLD << "----- TEST -----" << RESET << std::endl;

	Intern intern;
	AForm* form1 = intern.makeForm("shrubbery creation", "Home");
	AForm* form2 = intern.makeForm("robotomy request", "Bender");
	AForm* form3 = intern.makeForm("presidential pardon", "Arthur Dent");
	std::cout << std::endl;
	AForm* formBad = intern.makeForm("unknown form", "Nobody");
	formBad = intern.makeForm("coffee request", "Office");

	std::cout << std::endl;
	std::cout << BOLD << "----- BUREAUCRATS -----" << RESET << std::endl;

	Bureaucrat high("Master", 1);
	Bureaucrat mid("Worker", 50);
	Bureaucrat low("SomeIntern", 150);

	std::cout << high << std::endl;
	std::cout << mid << std::endl;
	std::cout << low << std::endl;

	std::cout << std::endl << BOLD << "--- Signing attempts ---" << RESET << std::endl;

	if (form1) mid.signForm(*form1);
	if (form2) mid.signForm(*form2);
	if (form3) mid.signForm(*form3);

	if (form2) high.signForm(*form2);
	if (form3) high.signForm(*form3);

	std::cout << std::endl << BOLD << "--- Execution attempts ---" << RESET << std::endl;

	if (form1) {
		low.executeForm(*form1);
		mid.executeForm(*form1);
	}

	if (form2) {
		mid.executeForm(*form2);
		high.executeForm(*form2);
	}

	if (form3) {
		mid.executeForm(*form3);
		high.executeForm(*form3);
	}

	std::cout << std::endl << BOLD << "----- CLEANUP -----" << RESET << std::endl;

	delete form1;
	delete form2;
	delete form3;
	delete formBad;

	std::cout << BOLD << "----- END TEST -----" << RESET << std::endl << std::endl;

	return 0;
}

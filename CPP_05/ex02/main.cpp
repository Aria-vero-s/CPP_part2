#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
	std::cout << std::endl;
	std::cout << BOLD << "----- TEST -----" << RESET << std::endl;
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	try {
		Bureaucrat high("Master", 1);
		Bureaucrat mid("Worker", 50);
		Bureaucrat low("Trainee", 150);

		ShrubberyCreationForm shrub("home");
		RobotomyRequestForm robo("Bender");
		PresidentialPardonForm pardon("Marvin");

		std::cout << shrub << std::endl;
		std::cout << robo << std::endl;
		std::cout << pardon << std::endl;
		std::cout << std::endl;

		std::cout << BOLD << "---- Signing ----" << RESET << std::endl;
		high.signForm(shrub);
		mid.signForm(shrub);
		low.signForm(robo);
		high.signForm(robo);
		mid.signForm(pardon);
		high.signForm(pardon);
		std::cout << std::endl;

		std::cout << BOLD << "---- Executions ----" << RESET << std::endl;
		low.executeForm(shrub);
		mid.executeForm(shrub);
		mid.executeForm(robo);
		high.executeForm(robo);
		high.executeForm(pardon);
		std::cout << std::endl;

	} catch (std::exception& e) {
		std::cout << RED "Unexpected exception: " << e.what() << RESET << std::endl;
	}
	std::cout << BOLD << "----- END TEST -----" << RESET << std::endl;
	std::cout << std::endl;

	return 0;
}
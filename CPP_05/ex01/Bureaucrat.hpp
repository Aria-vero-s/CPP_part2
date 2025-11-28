#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW   "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Form;

class Bureaucrat {
public:
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	Bureaucrat();
	Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& other);
	~Bureaucrat();
	Bureaucrat& operator=(const Bureaucrat& other);

	const std::string& getName() const;
	int getGrade() const;

	void incrementGrade();
	void decrementGrade();

	void signForm(Form& f) const; // new for ex01

private:
	const std::string name;
	int grade;

	void validateGrade(int g) const;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif

#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class AForm {
public:
	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what() const throw();
	};
	class FormNotSignedException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	AForm();
	AForm(const std::string& name, int gradeToSign, int gradeToExec);
	AForm(const AForm& other);
	virtual ~AForm();
	AForm& operator=(const AForm& other);

	const std::string& getName() const;
	bool isSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;

	void beSigned(const Bureaucrat& b);
	void execute(Bureaucrat const & executor) const;

	virtual void executeAction() const = 0;

private:
	const std::string name;
	bool signedFlag;
	const int gradeToSign;
	const int gradeToExec;

	void validateGrade(int g) const;
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif

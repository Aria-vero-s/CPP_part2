#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

const char* AForm::GradeTooHighException::what() const throw() {
	return "grade is too high";
}
const char* AForm::GradeTooLowException::what() const throw() {
	return "grade is too low";
}
const char* AForm::FormNotSignedException::what() const throw() {
	return "form is not signed";
}

AForm::AForm() : name("Unnamed"), signedFlag(false), gradeToSign(150), gradeToExec(150) {}

AForm::AForm(const std::string& n, int gSign, int gExec) : name(n), signedFlag(false), gradeToSign(gSign), gradeToExec(gExec) {
	validateGrade(gSign);
	validateGrade(gExec);
}

AForm::AForm(const AForm& other) : name(other.name), signedFlag(other.signedFlag), gradeToSign(other.gradeToSign), gradeToExec(other.gradeToExec) {}

AForm::~AForm() {}

AForm& AForm::operator=(const AForm& other) {
	if (this != &other)
		this->signedFlag = other.signedFlag;
	return *this;
}

const std::string& AForm::getName() const {
	return name;
}

bool AForm::isSigned() const {
	return signedFlag;
}

int AForm::getGradeToSign() const {
	return gradeToSign;
}

int AForm::getGradeToExecute() const {
	return gradeToExec;
}

void AForm::validateGrade(int g) const {
	if (g < 1)
		throw GradeTooHighException();
	if (g > 150)
		throw GradeTooLowException();
}

void AForm::beSigned(const Bureaucrat& b) {
	if (b.getGrade() > gradeToSign)
		throw GradeTooLowException();
	signedFlag = true;
}

void AForm::execute(Bureaucrat const & executor) const {
	if (!signedFlag)
		throw FormNotSignedException();
	if (executor.getGrade() > gradeToExec)
		throw GradeTooLowException();
	executeAction();
}

std::ostream& operator<<(std::ostream& os, const AForm& f) {
	os << "Form : " << BOLD << f.getName() << RESET << std::endl;
	os << "(signed: ";
	if (f.isSigned())
		os << "yes";
	else
		os << "no";
	os << ", sign grade: " << f.getGradeToSign()
	   << ", exec grade: " << f.getGradeToExecute() << ")";
	return os;
}

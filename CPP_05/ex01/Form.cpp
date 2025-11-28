#include "Form.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

const char* Form::GradeTooHighException::what() const throw() {
    return "grade is too high";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "grade is too low";
}

Form::Form() : name("Unnamed"), signedFlag(false), gradeToSign(150), gradeToExec(150) {}

Form::Form(const std::string& n, int gSign, int gExec)
    : name(n), signedFlag(false), gradeToSign(gSign), gradeToExec(gExec) {
    validateGrade(gSign);
    validateGrade(gExec);
}

Form::Form(const Form& other)
    : name(other.name), signedFlag(other.signedFlag),
      gradeToSign(other.gradeToSign), gradeToExec(other.gradeToExec) {}

Form::~Form() {}

Form& Form::operator=(const Form& other) {
    if (this != &other)
        this->signedFlag = other.signedFlag;
    return *this;
}

const std::string& Form::getName() const {
    return name;
}

bool Form::isSigned() const {
    return signedFlag;
}

int Form::getGradeToSign() const {
    return gradeToSign;
}

int Form::getGradeToExecute() const {
    return gradeToExec;
}

void Form::validateGrade(int g) const {
    if (g < 1)
        throw GradeTooHighException();
    if (g > 150)
        throw GradeTooLowException();
}

void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > gradeToSign)
        throw GradeTooLowException();
    signedFlag = true;
}

std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << f.getName() << " (signed: ";
    if (f.isSigned())
        os << "yes";
    else
        os << "no";
    os << ", sign grade: " << f.getGradeToSign() << ", exec grade: " << f.getGradeToExecute() << ")";
    return os;
}


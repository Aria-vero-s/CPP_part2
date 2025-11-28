#include "Bureaucrat.hpp"
#include "Form.hpp"

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "grade is too low";
}

Bureaucrat::Bureaucrat() : name("Unnamed"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string& n, int g) : name(n), grade(g) {
	validateGrade(g);
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other) {
		this->grade = other.grade;
	}
	return *this;
}

const std::string& Bureaucrat::getName() const {
	return name;
}

int Bureaucrat::getGrade() const {
	return grade;
}

void Bureaucrat::validateGrade(int g) const {
	if (g < 1)
		throw GradeTooHighException();
	if (g > 150)
		throw GradeTooLowException();
}

void Bureaucrat::incrementGrade() {
	validateGrade(grade - 1);
	--grade;
}

void Bureaucrat::decrementGrade() {
	validateGrade(grade + 1);
	++grade;
}

void Bureaucrat::signForm(Form& f) const {
    try {
        f.beSigned(*this);
        std::cout << GREEN << name << " signed " << f << RESET << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << name << " can’t sign " << f
                  << " because " << e.what() << RESET << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
	os << b.getName() << ", bureaucrat grade " << b.getGrade();
	return os;
}

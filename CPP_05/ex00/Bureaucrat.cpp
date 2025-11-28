#include "Bureaucrat.hpp"

// Exception messages
const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "grade is too low";
}

// Default constructor
Bureaucrat::Bureaucrat() : name("Unnamed"), grade(150) {}

// Param constructor
Bureaucrat::Bureaucrat(const std::string& n, int g) : name(n), grade(g) {
    validateGrade(g);
}

// Copy constructor
Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade) {}

// Destructor
Bureaucrat::~Bureaucrat() {}

// Assignment operator: name is const, so only copy grade
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {
        this->grade = other.grade;
        // name is const: cannot assign
    }
    return *this;
}

// Getters
const std::string& Bureaucrat::getName() const {
    return name;
}

int Bureaucrat::getGrade() const {
    return grade;
}

// Validate grade helper
void Bureaucrat::validateGrade(int g) const {
    if (g < 1)
        throw GradeTooHighException();
    if (g > 150)
        throw GradeTooLowException();
}

// increment: improve grade (3 -> 2)
void Bureaucrat::incrementGrade() {
    validateGrade(grade - 1); // check new grade
    --grade;
}

// decrement: worsen grade (3 -> 4)
void Bureaucrat::decrementGrade() {
    validateGrade(grade + 1); // check new grade
    ++grade;
}

// operator<<
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade();
    return os;
}

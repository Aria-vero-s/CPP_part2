#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Bureaucrat {
public:
    // Exceptions
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    // Orthodox Canonical Form
    Bureaucrat();                                  // default
    Bureaucrat(const std::string& name, int grade); // param
    Bureaucrat(const Bureaucrat& other);           // copy
    ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& other);

    // Getters
    const std::string& getName() const;
    int getGrade() const;

    // Operations
    void incrementGrade(); // improves grade: 3 -> 2
    void decrementGrade(); // lowers grade: 3 -> 4

private:
    const std::string name;
    int grade;

    void validateGrade(int g) const;
};

// non-member overload for printing
std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif // BUREAUCRAT_HPP

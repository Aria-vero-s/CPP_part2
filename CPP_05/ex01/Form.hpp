#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class Form {
public:
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    Form();
    Form(const std::string& name, int gradeToSign, int gradeToExec);
    Form(const Form& other);
    ~Form();
    Form& operator=(const Form& other);

    const std::string& getName() const;
    bool isSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;

    void beSigned(const Bureaucrat& b);

private:
    const std::string name;
    bool signedFlag;
    const int gradeToSign;
    const int gradeToExec;

    void validateGrade(int g) const;
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif

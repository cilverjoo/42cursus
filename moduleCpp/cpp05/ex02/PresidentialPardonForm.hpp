#ifndef PresidentialPardonForm_HPP
# define PresidentialPardonForm_HPP

#include <string>
#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

class Bureaucrat;

class PresidentialPardonForm : public Form
{

private:

    std::string _target;
	PresidentialPardonForm();

public:

	PresidentialPardonForm(std::string target);
    ~PresidentialPardonForm();
    PresidentialPardonForm(const PresidentialPardonForm& ref);
	PresidentialPardonForm& operator=(const PresidentialPardonForm& ref);

    void execute(Bureaucrat const & executor) const;

};

#endif

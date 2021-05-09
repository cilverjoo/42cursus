#ifndef INTERN_HPP
# define INTERN_HPP

#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{

public:
	Intern();
	Intern(const Intern& ref);
	~Intern();
	Intern& operator=(const Intern& ref);

	Form*   makeForm(std::string formName, std::string target);

	class InvalidTypeException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

};

#endif
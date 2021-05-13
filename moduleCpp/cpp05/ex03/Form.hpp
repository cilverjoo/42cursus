#ifndef FORM_HPP
# define FORM_HPP

#include <string>
#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
	const std::string	_name;
	bool				_signed;
	const int			_signGrade;
	const int			_executeGrade;
	Form();

public:
	Form(std::string name, int signGrade, int executeGrade);
	Form(const Form& ref);
	virtual ~Form();
	Form& operator=(const Form& ref);

	std::string 		getName() const;
	bool				getSigned() const;
	int					getSignGrade() const;
	int					getExecuteGrade() const;
	void				beSigned(Bureaucrat& ref);
	virtual void		execute(Bureaucrat const & executor) const = 0;

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
	class FormAlreadySignedException: public std::exception {
		virtual const char* what() const throw();
	};
	class FormUnsignedException : public std::exception {
		virtual const char* what() const throw();
	};
};

std::ostream& operator<<(std::ostream &os, const Form &ref);

#endif

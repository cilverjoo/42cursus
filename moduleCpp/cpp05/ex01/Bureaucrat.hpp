#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include "Form.hpp"

class Bureaucrat
{
private:
	int _grade;
	std::string _name;

public:
	Bureaucrat();
	Bureaucrat(std::string name, int grade);
	~Bureaucrat();
	Bureaucrat(const Bureaucrat &ref);
	Bureaucrat& operator=(const Bureaucrat &ref);
	
	std::string getName() const;
	int			getGrade() const;
	void		IncrementGrade();
	void		DecrementGrade();
	void		signForm(const Form &ref);
	
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
};

std::ostream	&operator<<(std::ostream &os, const Bureaucrat &b);

#endif

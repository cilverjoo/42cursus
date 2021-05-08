#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	if (grade > 150)
		throw(Bureaucrat::GradeTooHighException());
	else if (grade < 1)
		throw(Bureaucrat::GradeTooLowException());
	else
	{
		this->_grade = grade;
	}
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat::Bureaucrat(const Bureaucrat &ref)
{
	this->_name = ref._name;
	this->_grade = ref._grade;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &ref)
{
	this->_name = ref._name;
	this->_grade = ref._grade;
	return (*this);
}

std::string Bureaucrat::getName(void) const
{
	return (this->_name);
}

int			Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Error: Grade is lower than Minimun.");
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Error: Grade is higher than Maximum.");
}

void		Bureaucrat::signForm(const Form &ref)
{
	if (ref.getSigned() == true)
		std::cout << "<" << _name << "> signs <" << ref.getName() << ">" << std::endl;
	else
		std::cout << "<" << _name << "> cannot sign <" << ref.getName() << "> because <reason>" << std::endl;
}

void		Bureaucrat::IncrementGrade(void)
{
	if (this->_grade < 150)
		this->_grade++;
	else
		throw(Bureaucrat::GradeTooHighException());
}

void		Bureaucrat::DecrementGrade(void)
{
	if (this->_grade > 1)
		this->_grade--;
	else
		throw(Bureaucrat::GradeTooLowException());
	
}

std::ostream& operator<<(std::ostream &os, const Bureaucrat &ref)
{
	os << "<" << ref.getName() << ", bureaucrat grade <" << ref.getGrade() << ">." << std::endl;	return (os);
	return (os);
}

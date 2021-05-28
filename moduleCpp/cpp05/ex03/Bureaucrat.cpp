#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	if (grade > 150)
		throw(Bureaucrat::GradeTooLowException());
	else if (grade < 1)
		throw(Bureaucrat::GradeTooHighException());
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
	*this = ref;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &ref)
{
	if (this == &ref)
		return (*this);
	this->_name = ref.getName();
	this->_grade = ref.getGrade();
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
	return ("Error: Grade is Too Low !");
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Error: Grade is Too High !");
}

void		Bureaucrat::DecrementGrade(void)
{
	if (this->_grade < 150)
		this->_grade++;
	else
		throw(Bureaucrat::GradeTooLowException());
}

void		Bureaucrat::IncrementGrade(void)
{
	if (this->_grade > 1)
		this->_grade--;
	else
		throw(Bureaucrat::GradeTooHighException());
}

void		Bureaucrat::signForm(Form &form) const
{
	if (form.getSigned() == true)
		std::cout << "<" << this->getName() << "> cannot sign <" << form.getName() << "> because it is already signed.\n";
	else if (this->getGrade() <= form.getSignGrade())
		std::cout << "<" << this->getName() << "> signs <" << form.getName() << ">.\n";
	else
		std::cout << "<" << this->getName() << "> cannot sign <" << form.getName() << "> because grade is too low :(\n";
	form.beSigned(*this);
}

void		Bureaucrat::executeForm(Form const & form) const
{
	try
	{
		form.execute(*this);
		std::cout << "<" << _name << "> executes <" << form.getName() << ">\n";
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::ostream& operator<<(std::ostream &os, const Bureaucrat &ref)
{
	os << "<" << ref.getName() << ">, bureaucrat grade <" << ref.getGrade() << ">." << std::endl;
	return (os);
}

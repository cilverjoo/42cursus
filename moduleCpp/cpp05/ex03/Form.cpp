#include "Form.hpp"

Form::Form(std::string name, int signGrade, int executeGrade) : _name(name), _signed(false), _signGrade(signGrade), _executeGrade(executeGrade)
{
	if (_signGrade > 150 ||_executeGrade > 150 )
		throw(Form::GradeTooLowException());
	else if (_signGrade < 1 || _executeGrade < 1)
		throw(Form::GradeTooHighException());
}

Form::~Form()
{
}

Form::Form(const Form &ref) : _name(ref.getName()), _signed(ref.getSigned()), _signGrade(ref.getSignGrade()), _executeGrade(ref.getExecuteGrade())
{
	*this = ref;
} 

Form& Form::operator=(const Form &ref)
{
	if (this == &ref)
		return (*this);
	this->_signed = ref._signed;
	return (*this);
}

std::string Form::getName(void) const
{
	return (this->_name);
}

bool		Form::getSigned() const
{
	return (this->_signed);
}

int			Form::getSignGrade() const
{
	return (this->_signGrade);
}

int			Form::getExecuteGrade() const
{
	return (this->_executeGrade);
}

void		Form::beSigned(Bureaucrat const &ref)
{
	if (ref.getGrade() > this->getSignGrade())
		throw (Form::GradeTooLowException());
	else if (this->getSigned() == true)
		throw (Form::FormAlreadySignedException());
	this->_signed = true;
}

void		Form::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->_executeGrade)
		throw (Form::GradeTooLowException());
	if (this->_signed == false)
		throw (Form::FormUnsignedException());
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Error: Grade is Too low.");
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Error: Grade is Too high.");
}

const char* Form::FormAlreadySignedException::what() const throw()
{
	return ("Error: This Form is already signed");
}

const char* Form::FormUnsignedException::what() const throw()
{
	return ("Error: This form is unsigned");
}

std::ostream& operator<<(std::ostream &os, const Form &ref)
{
	os << "<" << ref.getName() << ">, Form  sign state is " << ref.getSigned() << " and SignGrade is " 
		<< ref.getSignGrade() << " and Execute Grade is " << ref.getExecuteGrade() << std::endl;
	return (os);
}

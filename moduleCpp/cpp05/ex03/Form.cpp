#include "Form.hpp"

Form::Form(std::string name, int signGrade, int executeGrade) : _name(name), _signed(false), _signGrade(signGrade), _executeGrade(executeGrade)
{
	if (_signGrade > 150 || _executeGrade > 150 )
		throw(Form::GradeTooLowException());
	else if (_signGrade < 1 || _executeGrade < 1)
		throw(Form::GradeTooHighException());
}

Form::~Form()
{
}

Form::Form(Form const &ref):
	_name(ref.getName()), _signed(ref.getSigned()), _signGrade(ref.getSignGrade()), _executeGrade(ref.getExecuteGrade())
{
	if (_signGrade < 1 || _executeGrade < 1)
		throw (Form::GradeTooHighException());
	else if (_signGrade > 150 || _executeGrade > 150)
		throw (Form::GradeTooLowException());
}

Form& Form::operator=(const Form &ref)
{
	this->_signed = ref.getSigned();
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

void        Form::beSigned(Bureaucrat& ref)
{
	if (this->_signGrade < ref.getGrade())
		throw (Form::GradeTooLowException());
	else if (this->_signed)
		throw (Form::FormAlreadySignedException());
	this->_signed = true;
	return ;
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
	return ("FormException: The Form is already signed");
}

const char* Form::FormUnsignedException::what() const throw()
{
	return ("FormException: This form is unsigned");
}

void		Form::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->_executeGrade)
		throw (Form::GradeTooLowException());
	if (this->_signed == false)
		throw (Form::FormUnsignedException());
}

std::ostream& operator<<(std::ostream &os, const Form &ref)
{
	os << "<" << ref.getName() << ">, Form  sign state is " << ref.getSigned() << " and SignGrade is " 
		<< ref.getSignGrade() << " and Execute Grade is " << ref.getExecuteGrade() << std::endl;
	return (os);
}

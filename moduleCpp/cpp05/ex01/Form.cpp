#include "Form.hpp"

Form::Form(std::string name, int signGrade, int executeGrade) : _name(name), _signed(false), _signGrade(signGrade), _executeGrade(executeGrade)
{
	if (_signGrade > 150 ||_executeGrade > 150 )
		throw(Form::GradeTooHighException());
	else if (_signGrade < 1 || _executeGrade < 1)
		throw(Form::GradeTooLowException());
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
	if (_signGrade <= ref.getGrade())
		this->_signed = true;
	else
		throw(Form::GradeTooLowException());
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

std::ostream& operator<<(std::ostream &os, const Form &ref)
{
	os << "<" << ref.getName() << ">, Form  sign state is " << ref.getSigned() << " and SignGrade is " 
		<< ref.getSignGrade() << " and Execute Grade is " << ref.getExecuteGrade() << std::endl;
	return (os);
}

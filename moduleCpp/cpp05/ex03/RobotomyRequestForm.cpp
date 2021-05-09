#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form("Robotomy Request", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &ref) : Form(ref), _target(ref._target)
{
}


RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &ref)
{
    if (this == &ref)
        return (*this);
    Form::operator=(ref);
    this->_target = ref._target;
	return (*this);
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
    Form::execute(executor);
    std::cout << "* rizzz...bzzz... *" << std::endl;
    srand(clock());
    if(rand() % 2)
        std::cout << _target << " has been robotomized succesfully." << std::endl;
    else
        std::cout << _target << " robotomization has failed." << std::endl;
}
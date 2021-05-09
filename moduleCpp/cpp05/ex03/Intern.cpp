#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern& ref)
{
    *this = ref;
}

Intern&         Intern::operator=(const Intern& ref)
{
    return (*this);
}

Intern::~Intern()
{
}

const char*     Intern::InvalidTypeException::what() const throw()
{
    return ("InternExeption: Invalid Type");
}

Form*           Intern::makeForm(std::string formName, std::string target)
{
    std::string targets[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
    Form        *forms[3];
	Form        *result = 0;
    int         target;

    forms[0] = new ShrubberyCreationForm(target);
    forms[1] = new RobotomyRequestForm(target);
    forms[2] = new PresidentialPardonForm(target);
    for (int i = 0; i < 3; i++)
    {
        if (formName == targets[i])
        {
            target = i;
            std::cout << "Intern creates " << formName << " form.\n";
            result = forms[i];
            continue ;
        }
        delete forms[i];
    }
    if (!result)
    	throw (Intern::InvalidTypeException());
    return (result);
}

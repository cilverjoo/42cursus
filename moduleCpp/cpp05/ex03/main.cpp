#include <iostream>
#include "Intern.hpp"
#include "Form.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void)
{
	srand(time(NULL));
	Intern someIntern;

	Bureaucrat supervisor("Supervisor_1", 1);
	std::cout << supervisor << std::endl;
	Bureaucrat francis("Francis_25", 25);
	std::cout << francis << std::endl;

	Form *shrub = someIntern.makeForm("Shrubbery Creation", "tree");
	std::cout << *shrub << std::endl;
	shrub->beSigned(supervisor);
	std::cout << *shrub << std::endl;
	try
	{
		shrub->execute(francis);
		std::cout << "Shrubbery Creation success.\n";
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
	std::cout << "=============================" << std::endl;

	Form *pres = someIntern.makeForm("Presidential Pardon", "Francis");
	std::cout << *pres << std::endl;
	supervisor.signForm(*pres);
	std::cout << *pres << std::endl;
	try
	{
		pres->execute(supervisor);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << "=============================" << std::endl;

	Form *robot = someIntern.makeForm("Robotomy Request", "Bender");
	std::cout << *robot << std::endl;
	robot->beSigned(supervisor);
	francis.executeForm(*robot);
	francis.executeForm(*robot);

	std::cout << "=============================" << std::endl;

	try
	{
		Form *ran = someIntern.makeForm("Exception", "nobody");
		std::cout << ran << std::endl;
	}
	catch(std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}

	delete shrub;
	delete pres;
	delete robot;
	
	return (0);
}

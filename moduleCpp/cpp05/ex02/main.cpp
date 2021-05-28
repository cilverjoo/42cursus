#include <iostream>
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void)
{
	srand(time(NULL));

	Bureaucrat supervisor("Supervisor_1", 1);
	std::cout << supervisor << std::endl;
	Bureaucrat francis("fransis_25", 25);
	std::cout << francis << std::endl;

	Form *shrub = new ShrubberyCreationForm("Target");
	std::cout << *shrub << std::endl;
	
	try
	{
		shrub->beSigned(supervisor);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}
	
	std::cout << *shrub << std::endl;

	try
	{
		shrub->execute(supervisor);
		std::cout << "shrub execute success\n";
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
	Form *pres = new PresidentialPardonForm("Presidential_25_5");
	std::cout << *pres << std::endl;
	
	try
	{
		supervisor.signForm(*pres);
		pres->execute(supervisor);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
	Form *robot = new RobotomyRequestForm("Robodomy_72_45");
	std::cout << *robot << std::endl;
	
	try
	{
		robot->beSigned(supervisor);
		std::cout << *robot << std::endl;
		robot->execute(francis);
		francis.executeForm(*robot);
		francis.executeForm(*robot);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
	std::cout << "=============================" << std::endl;

	try
	{
		francis.executeForm(*pres);
	}
	catch(std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "=============================" << std::endl;

	try
	{
		RobotomyRequestForm robot = RobotomyRequestForm("Bender_72_45");
		std::cout << robot << std::endl;
		robot.execute(supervisor);
	}
	catch(std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "=============================" << std::endl;

	try
	{
		PresidentialPardonForm pres = PresidentialPardonForm("Jeff_25_5");
		std::cout << pres << std::endl;
		supervisor.signForm(pres);
		pres.execute(supervisor);
	}
	catch(std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "=============================" << std::endl;

	try
	{
		PresidentialPardonForm pres = PresidentialPardonForm("Pres_25_5");
		std::cout << pres << std::endl;
		supervisor.signForm(pres);
		francis.executeForm(pres);
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

#include "Bureaucrat.hpp"
#include "Form.hpp"

int     main(void)
{
	Form 		*f1;
	try
	{
		f1 = new Form("f1", 0, 10);
	}
	catch(const std::exception &e)
	{
		std::cout<<e.what()<<'\n';
	}

	Bureaucrat	b("b", 50);
	Form 		f2("f2", 60, 10);
	Form 		f3("f3", 40, 10);
	try
	{
		b.signForm(f2);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		b.signForm(f3);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
    return 0;
}

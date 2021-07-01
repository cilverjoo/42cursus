#include <vector>
#include "easyfind.hpp"

int		main(void)
{
	std::vector<int> vec;
	
	std::cout << "Empty vec test" << std::endl;
	try
	{
		std::cout << easyfind(vec, 10) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	vec.push_back(10);
	vec.push_back(42);
	
	std::cout << "add 10 & 42" << std::endl;
	
	try
	{
		std::cout << easyfind(vec, 10) << std::endl;
		std::cout << easyfind(vec, 42) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}	
	
	std::cout << "try to find unexisting values" << std::endl;
	try
	{
		std::cout << easyfind(vec, -10) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}

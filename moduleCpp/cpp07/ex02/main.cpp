#include <iostream>
#include "Array.hpp"

int		main(void)
{
	Array<int> tab(3);

	std::cout << "-- int test" << std::endl;
	tab[0] = 1;
	tab[1] = 2;
	tab[2] = 3;
	std::cout << "tab size: " << tab.size() << std::endl;
	std::cout << "tab[" << tab[0] << ", " << tab[1] << ", " << tab[2] << "]";
	std::cout << std::endl;

	std::cout << std::endl;
	
	std::cout << "-- copying tab and modify a value" << std::endl;
	Array<int> cpy(tab);
	cpy[1] = 42;
	std::cout << "tab size: " << tab.size() << std::endl;
	std::cout << "tab[" << tab[0] << ", " << tab[1] << ", " << tab[2] << "]";
	std::cout << std::endl;
	std::cout << "cpy size: " << cpy.size() << std::endl;
	std::cout << "cpy[" << cpy[0] << ", " << cpy[1] << ", " << cpy[2] << "]";
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "-- string test" << std::endl;
	Array<std::string> arr(3);
	arr[0] = "bla";
	arr[1] = "blo";
	arr[2] = "bli";
	std::cout << "arr size: " << arr.size() << std::endl;
	std::cout << "arr[" << arr[0] << ", " << arr[1] << ", " << arr[2] << "]";
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "-- test exception" << std::endl;
	try
	{
		std::cout << tab[3] << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "exception catched" << std::endl;
	}
	return (0);
}
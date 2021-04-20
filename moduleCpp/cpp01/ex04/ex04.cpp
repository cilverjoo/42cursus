#include <iostream>
#include <string>

int			main(void)
{
	std::string str;
	std::string *ptr;

	str = "HI THIS IS BRAIN";
	ptr = &str;
	std::string &ref = str;
<<<<<<< HEAD
	std::cout << "str : " << str << std::endl;
	std::cout << "ptr : " << *ptr << std::endl;
	std::cout << "ref : " << ref << std::endl;
	return (0);
}
=======
	std::cout << str << std::endl;
	std::cout << ptr << std::endl;
	std::cout << ref << std::endl;

	return (0);
}
>>>>>>> 17e848ba9fbdce19a5e8dbe7ac37d85467df7214

#include "contact.hpp"

std::string Contact::get_firstName()
{
	return (this->firstName);
}

std::string Contact::get_lastName()
{
	return (this->lastName);
}

std::string Contact::get_nickName()
{
	return (this->nickName);
}

void		Contact::set_firstName(std::string str)
{
	this->firstName = str;
	return ;
}

#include "Victim.hpp"

Victim::Victim()
{
	name = "unknown";
	std::cout << "Some random victim called " << name << " just appeared!" << std::endl;
}

Victim::Victim(std::string _name) : name(_name)
{
	std::cout << "Some random victim called " << name << " just appeared!" << std::endl;
}

Victim::~Victim()
{
	std::cout << "Victim " << name << " just died for no apparent reason!" << std::endl;
}

Victim::Victim(const Victim &ref)
{
	this->name = ref.name;
    *this = ref;
}

Victim			&Victim::operator=(const Victim & ref)
{
	this->name = ref.name;
    return (*this);
}

std::string		Victim::getName() const
{
	return (name);
}

void			Victim::getPolymorphed() const
{
	std::cout << name << " has been turned into a cute little sheep!" << std::endl;
}

std::ostream	&operator<<(std::ostream &os, const Victim &ref)
{
	os << "I'm " << ref.getName() <<  " and I like otters!\n";
	return (os);
}

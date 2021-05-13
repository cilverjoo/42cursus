#include "Peon2.hpp"
#include "Victim.hpp"

Peon2::Peon2() : Victim()
{
	std::cout << "Zog zog." << std::endl;
}

Peon2::~Peon2()
{
	std::cout << "Bleuark..." << std::endl;
}

Peon2::Peon2(std::string _name) : Victim(_name)
{
	std::cout << "Zog zog." << std::endl;
}

Peon2::Peon2(const Peon2 &ref) : Victim(ref)
{
}

Peon2	&Peon2::operator=(const Peon2 & ref)
{
	this->name = ref.name;
	std::cout << "Zog zog." << std::endl;
    return (*this);
}

void    Peon2::getPolymorphed() const
{
	std::cout << name << " has been turned into a Puss in Boots!\n";
}

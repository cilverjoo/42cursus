#include "Peon.hpp"
#include "Victim.hpp"

Peon::Peon() : Victim()
{
	std::cout << "Zog zog." << std::endl;
}

Peon::~Peon()
{
	std::cout << "Bleuark..." << std::endl;
}

Peon::Peon(std::string _name) : Victim(_name)
{
	std::cout << "Zog zog." << std::endl;
}

Peon::Peon(const Peon &ref) : Victim(ref)
{
}

Peon	&Peon::operator=(const Peon & ref)
{
	this->name = ref.name;
	std::cout << "Zog zog." << std::endl;
    return (*this);
}

void    Peon::getPolymorphed() const
{
	std::cout << name << " has been turned into a pink pony!\n";
}

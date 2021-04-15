#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
	this->name = name;
}

HumanB::~HumanB()
{
}

void			HumanB::setWeapon(Weapon &club)
{
	this->weapon = &club;
}

void			HumanB::setType(std::string type)
{
	(*this->weapon).setType(type);
}

void			HumanB::attack()
{
	std::cout << this->name 
		<< " attacks with his " << (*this->weapon).getType() << std::endl;
}

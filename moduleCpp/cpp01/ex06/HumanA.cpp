#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &club) : weapon(club)
{
	this->name = name;
}

HumanA::~HumanA()
{
}

void			HumanA::attack()
{
	std::cout << this->name 
		<< " attacks with his " << this->weapon.getType() << std::endl;
}

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &club) : _name(name), _weapon(club)
{
}

HumanA::~HumanA()
{
}

void			HumanA::attack() const
{
	std::cout << _name 
		<< " attacks with his " << _weapon.getType() << std::endl;
}

#include "PowerFist.hpp"

PowerFist::PowerFist() : AWeapon("Power Fist", 8, 50)
{
}

PowerFist::~PowerFist()
{
	
}

PowerFist::PowerFist(const PowerFist &ref) : AWeapon(ref)
{
}

PowerFist &PowerFist::operator=(const PowerFist &ref)
{
	_name = ref._name;
	_damage = ref._damage;
	_apcost = ref._apcost;
	return (*this);
}

void PowerFist::attack() const
{
	std::cout << "* pschhh... SBAM! *" << std::endl;
}

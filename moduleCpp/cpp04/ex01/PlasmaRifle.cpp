#include "PlasmaRifle.hpp"

PlasmaRifle::PlasmaRifle() : AWeapon("Plasma Rifle", 5, 21)
{
}

PlasmaRifle::~PlasmaRifle()
{	
}

PlasmaRifle::PlasmaRifle(const PlasmaRifle &ref) : AWeapon(ref)
{
}

PlasmaRifle &PlasmaRifle::operator=(const PlasmaRifle &ref)
{
	_name = ref.getName();
	_damage = ref.getDamage();
	_ap= ref.getAPCost();
	return (*this);
}

void PlasmaRifle::attack() const
{
	std::cout << "* piouuu piouuu piouuu *" << std::endl;
}

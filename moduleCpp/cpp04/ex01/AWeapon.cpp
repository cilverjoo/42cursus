#include "AWeapon.hpp"

AWeapon::AWeapon(std::string const & name, int apcost, int damage) : _name(name), _apcost(apcost), _damage(damage)
{	
}

AWeapon::~AWeapon()
{	
}

AWeapon::AWeapon(const AWeapon &ref)
{
	*this = ref;
}

AWeapon			&AWeapon::operator=(const AWeapon &ref)
{
	_apcost = ref.getAPCost();
	_damage = ref.getDamage();
	_name = ref.getName();
	return (*this);
}

std::string 	AWeapon::getName(void) const
{
	return (this->_name);
}

int				AWeapon::getAPCost(void) const
{
	return (this->_apcost);
}

int				AWeapon::getDamage(void) const
{
	return (this->_damage);
}

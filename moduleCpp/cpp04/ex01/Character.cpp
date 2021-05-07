#include "Character.hpp"

Character::Character(std::string const &name) : _name(name), _ap(40), _weapon(NULL) 
{
}

Character::~Character()
{
	
}

Character::Character(const Character &ref)
{
	this->_ap = ref.getAP();
	this->_name = ref.getName();
	this->_weapon = ref.getWeapon();
}

void 			Character::recoverAP()
{
	if (_ap + 10 >= 40)
		std::cout << "AP is FULL :(" << std::endl;
	else
		_ap += 10;	
}

void 			Character::attack(Enemy *enemy)
{
	if (_weapon == NULL || _ap < _weapon->getAPCost())
		return ;
	std::cout << _name << " attacks " << enemy->getType() << " with a " << _weapon->getName() << std::endl;
	_weapon->attack();
	_ap -= _weapon->getAPCost();
	enemy->takeDamage(_weapon->getDamage());
	if (enemy->getHP() <= 0)
		enemy->~Enemy();
}

void 			Character::equip(AWeapon *newWep)
{
	this->_weapon = newWep;
}

std::string		Character::getName(void) const
{
	return (this->_name);	
}

int				Character::getAP(void) const
{
	return (this->_ap);
}

AWeapon*		Character::getWeapon(void) const
{
	return (this->_weapon);
}

std::ostream 	&operator<<(std::ostream &os, const Character &ref)
{
	if (ref.getWeapon() == NULL)
		os << ref.getName() << " has " << ref.getAP() << " AP and is unarmed\n";
	else
		os << ref.getName() << " has " << ref.getAP() << " AP and wields a " << ref.getWeapon()->getName() << std::endl;	
	return (os);
}

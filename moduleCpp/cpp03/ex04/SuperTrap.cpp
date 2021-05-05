#include "SuperTrap.hpp"

SuperTrap::SuperTrap()
{
    _name = "unknown";
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 120;
    _maxEnergyPoint = 120;
    _level = 1;
    _meleeAttackDamage = 60;
    _rangedAttackDamage = 20;
    _armorDamageReduction = 5;
	std::cout<<"[SUPER] "<< _name << " player joined the game!\n";
}

SuperTrap::SuperTrap(std::string name)
{
    _name = name;
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 120;
    _maxEnergyPoint = 120;
    _level = 1;
    _meleeAttackDamage = 60;
    _rangedAttackDamage = 20;
    _armorDamageReduction = 5;
	std::cout<<"[SUPER] " << _name << " player joined the game!\n";
}

SuperTrap::SuperTrap(const SuperTrap & ref)
{
    *this = ref;
	std::cout<<"[SUPER] "<< _name <<" player joined the game!\n";	
}

SuperTrap& SuperTrap::operator=(const SuperTrap & ref)
{
    _name = ref._name;
    _hitPoint = ref._hitPoint;
    _maxHitPoint = ref._maxHitPoint;
    _energyPoint = ref._energyPoint;
    _maxEnergyPoint = ref._maxEnergyPoint;
    _level = ref._level;
    _meleeAttackDamage = ref._meleeAttackDamage;
    _rangedAttackDamage = ref._rangedAttackDamage;
    _armorDamageReduction = ref._armorDamageReduction;
    return (*this);    
}

SuperTrap::~SuperTrap()
{
	std::cout<<"[SUPER] "<<_name<<" player left the game!\n";
}

unsigned int    SuperTrap::rangedAttack(std::string const &target)
{
    return (FragTrap::rangedAttack(target));
}

unsigned int    SuperTrap::meleeAttack(std::string const &target)
{
    return (NinjaTrap::meleeAttack(target));
}

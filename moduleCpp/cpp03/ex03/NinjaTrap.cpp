#include "NinjaTrap.hpp"

NinjaTrap::NinjaTrap() : ClapTrap()
{
    _hitPoint = 60;
    _maxHitPoint = 60;
    _energyPoint = 120;
    _maxEnergyPoint = 120;
    _level = 1;
    _meleeAttackDamage = 6;
    _rangedAttackDamage = 5;
    _armorDamageReduction = 0;
    std::cout << "[NinjaTrap] Create Player " << "<" << _name << "> !\n";
}

NinjaTrap::NinjaTrap(std::string name) : ClapTrap(name)
{
    _hitPoint = 60;
    _maxHitPoint = 60;
    _energyPoint = 120;
    _maxEnergyPoint = 120;
    _level = 1;
    _meleeAttackDamage = 6;
    _rangedAttackDamage = 5;
    _armorDamageReduction = 0;
    std::cout << "[NinjaTrap] Create Player " << "<" << _name << ">\n";
}

NinjaTrap::~NinjaTrap()
{
    std::cout <<  "[NinjaTrap]" << " < " << _name << " >" << " left this game." << std::endl;
}

NinjaTrap::NinjaTrap(const NinjaTrap &ref)
{
    *this = ref;
    std::cout << "[NinjaTrap] Create Player " << "<" << _name << ">\n";
}

NinjaTrap &NinjaTrap::operator=(const NinjaTrap &ref)
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

void   NinjaTrap::ninjaShoebox(const FragTrap &ref)
{
    std::cout<<"[NINJA's FragTrap] "<< _name << " attacks " << ref._name << " with [Throwing Blades]" << std::endl;
}

void   NinjaTrap::ninjaShoebox(const ScavTrap &ref)
{
    std::cout<<"[NINJA's ScavTrap] "<< _name <<" attacks " << ref._name <<  " with [Explosion]" << std::endl;
}

void   NinjaTrap::ninjaShoebox(const ClapTrap &ref)
{
    std::cout<<"[NINJA's ClapTrap] "<< _name << " attacks " << ref._name <<  " with [Ninja Sword]" << std::endl;
}

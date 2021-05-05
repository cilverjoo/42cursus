#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
    _name = "unknown";
    std::cout << "Create Player " << "<" << _name << ">\n";
}

ClapTrap::ClapTrap(std::string name)
{
    _name = name;
    std::cout << "Create Player " << "<" << _name << ">\n";
}

ClapTrap::~ClapTrap()
{
    std::cout << "<" << _name << ">" << " left this game." << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy)
{
    *this = copy;
    std::cout << "Create Player " << "<" << _name << ">\n";
}

ClapTrap &ClapTrap::operator=(const ClapTrap &ft)
{
    _name = ft._name;
    _hitPoint = ft._hitPoint;
    _maxHitPoint = ft._maxHitPoint;
    _energyPoint = ft._energyPoint;
    _maxEnergyPoint = ft._maxEnergyPoint;
    _level = ft._level;
    _meleeAttackDamage = ft._meleeAttackDamage;
    _rangedAttackDamage = ft._rangedAttackDamage;
    _armorDamageReduction = ft._armorDamageReduction;
    return (*this);
}

unsigned int ClapTrap::rangedAttack(std::string const &target)
{
    std::cout << "FR4G-TP " << _name << " attacks " << target << " at range, causing "
        << this->_rangedAttackDamage << " points of damage\n";
    return (_rangedAttackDamage);    
}

unsigned int ClapTrap::meleeAttack(std::string const & target)
{
    std::cout << "FR4G-TP " << _name << " attacks " << target << " at melee, causing "
        << _meleeAttackDamage << " points of damage\n";
    return (_meleeAttackDamage);
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (_hitPoint - (amount - _armorDamageReduction) <= 0)
    {
        _hitPoint = 0;
        std::cout << "Player " << _name << " is DEAD :(\n";
    }
    else
	{
		_hitPoint -= amount - _armorDamageReduction;
		std::cout << "< " << _name << " > " << _hitPoint << " HP left :(" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (_hitPoint + amount >= _maxHitPoint)
        _hitPoint = _maxHitPoint;
    else
        _hitPoint += amount;
	std::cout << "< " << _name << " > recovered " << amount << "HP!\n";
}

void ClapTrap::show_status(void)
{
    std::cout << "----------------------------------" << std::endl;
    std::cout << "        " << _name << "'s status" << std::endl;
    std::cout << "HP : "<< _hitPoint << std::endl;
    std::cout << "Energy Point : " << _energyPoint << std::endl;
    std::cout << "----------------------------------" << std::endl;
}

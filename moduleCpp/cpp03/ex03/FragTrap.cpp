#include "FragTrap.hpp"
#include "ClapTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 100;
    _maxEnergyPoint = 100;
    _level = 1;
    _meleeAttackDamage = 30;
    _rangedAttackDamage = 20;
    _armorDamageReduction = 5;
    std::cout << "[FragTrap] Create Player " << "<" << _name << ">\n";
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 100;
    _maxEnergyPoint = 100;
    _level = 1;
    _meleeAttackDamage = 30;
    _rangedAttackDamage = 20;
    _armorDamageReduction = 5;
    std::cout << "[FragTrap] Create Player " << "<" << _name << ">\n";
}

FragTrap::~FragTrap()
{
    std::cout << "<" << _name << ">" << " left this game." << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy)
{
    *this = copy;
    std::cout << "[FragTrap] Create Player " << "<" << _name << ">\n";
}

FragTrap &FragTrap::operator=(const FragTrap &ft)
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

unsigned int FragTrap::vaulthunter_dot_exe(std::string const & target)
{
    std::string     randAttack[] = {"Relentless Shot", "Justice Strike", "Lightning Flash", "Chain Slash"};
    int             randDamage[] = {10, 15, 20, 50};
    int             rd;

    if (_energyPoint >= 25)
    {
        srand(time(NULL));
        rd = rand() % 4;
        std::cout << "[ " << randAttack[rd] << " ]" << " attacks " <<  _name << " with damage " << randDamage[rd] << " ! o_o\n";
        _energyPoint -= 25;
    }
    else
        std::cout << "Energy is not enough for \"vaulthunter_dot_exe\"!\n";
    return (randDamage[rd]);
}

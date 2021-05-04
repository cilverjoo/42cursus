#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 50;
    _maxEnergyPoint = 100;
    _level = 1;
    _meleeAttackDamage = 20;
    _rangedAttackDamage = 15;
    _armorDamageReduction = 3;
    _name = "unknown";
    std::cout << "Create Player " << "<" << _name << "> !\n";
}

ScavTrap::ScavTrap(std::string name)
{
    _name = name;
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 50;
    _maxEnergyPoint = 100;
    _level = 1;
    _meleeAttackDamage = 20;
    _rangedAttackDamage = 15;
    _armorDamageReduction = 3;
    std::cout << "Create Player " << "<" << _name << ">\n";
}

ScavTrap::~ScavTrap()
{
    std::cout << "<" << _name << ">" << " leave this game." << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &copy)
{
    *this = copy;
    std::cout << "Create Player " << "<" << _name << ">\n";
}

ScavTrap &ScavTrap::operator=(const ScavTrap &st)
{
    _name = st._name;
    _hitPoint = st._hitPoint;
    _maxHitPoint = st._maxHitPoint;
    _energyPoint = st._energyPoint;
    _maxEnergyPoint = st._maxEnergyPoint;
    _level = st._level;
    _meleeAttackDamage = st._meleeAttackDamage;
    _rangedAttackDamage = st._rangedAttackDamage;
    _armorDamageReduction = st._armorDamageReduction;
    return (*this);
}

unsigned int ScavTrap::rangedAttack(std::string const &target)
{
    std::cout << "FR4G-TP " << _name << " attacks " << target << " at range, causing "
        << this->_rangedAttackDamage << " points of damage\n";
    return (_rangedAttackDamage);    
}

unsigned int ScavTrap::meleeAttack(std::string const & target)
{
    std::cout << "FR4G-TP " << _name << " attacks " << target << " at melee, causing "
        << _meleeAttackDamage << " points of damage\n";
    return (_meleeAttackDamage);
}

void ScavTrap::takeDamage(unsigned int amount)
{
    if (_hitPoint - (amount - _armorDamageReduction) <= 0)
    {
        _hitPoint = 0;
        std::cout << "Player " << _name << " is DEAD :(\n";
    }
    else
        _hitPoint -= amount - _armorDamageReduction;
}

void ScavTrap::beRepaired(unsigned int amount)
{
    if (_hitPoint + amount >= _maxHitPoint)
        _hitPoint = _maxHitPoint;
    else
        _hitPoint += amount;
}

void ScavTrap::challengeNewcomer(void)
{
    std::string challenge[] = {"Wake up at 4am :(", "Defeat The Dread Dormammu",
        "Ask for bargain to Dormammu", "Forget everything that you think you know",
        "Complete common curriculum in 6 month :("};
    int         idx;
    
    usleep(100);    
    srand(clock());
    idx = rand() % 5;
    std::cout << "[ " << challenge[idx] << " ]" << std::endl;
}

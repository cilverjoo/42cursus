#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 50;
    _maxEnergyPoint = 100;
    _level = 1;
    _meleeAttackDamage = 20;
    _rangedAttackDamage = 15;
    _armorDamageReduction = 3;
    std::cout << "[ScavTrap] Create Player " << "<" << _name << "> !\n";
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
    _hitPoint = 100;
    _maxHitPoint = 100;
    _energyPoint = 50;
    _maxEnergyPoint = 100;
    _level = 1;
    _meleeAttackDamage = 20;
    _rangedAttackDamage = 15;
    _armorDamageReduction = 3;
    std::cout << "[ScavTrap] Create Player " << "<" << _name << ">\n";
}

ScavTrap::~ScavTrap()
{
    std::cout << "[ScavTrap] <" << _name << ">" << " left this game." << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &ref)
{
    *this = ref;
    std::cout << "[ScavTrap] Create Player " << "<" << _name << ">\n";
}

ScavTrap &ScavTrap::operator=(const ScavTrap &ref)
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

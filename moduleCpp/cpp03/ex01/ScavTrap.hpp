#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

class ScavTrap
{

private:
    int _hitPoint;
    int _maxHitPoint;
    int _energyPoint;
    int _maxEnergyPoint;
    int _level;
    unsigned int _meleeAttackDamage;
    unsigned int _rangedAttackDamage;
    int _armorDamageReduction;

public:
    std::string _name;
    ScavTrap();
    ScavTrap(std::string name);
    ~ScavTrap();
    ScavTrap(const ScavTrap&copy);
    ScavTrap &operator=(const ScavTrap &ft);
    std::string  getName();
    unsigned int rangedAttack(std::string const & target);
    unsigned int meleeAttack(std::string const & target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
    void challengeNewcomer(void);

};

#endif

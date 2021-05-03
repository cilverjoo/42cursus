#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

class FragTrap
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
    FragTrap();
    FragTrap(std::string name);
    ~FragTrap();
    FragTrap(const FragTrap &copy);
    FragTrap &operator=(const FragTrap &ft);
    std::string  getName();
    unsigned int rangedAttack(std::string const & target);
    unsigned int meleeAttack(std::string const & target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
    unsigned int vaulthunter_dot_exe(std::string const & target);

};

#endif
#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap
{

protected:
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
    ClapTrap();
    ClapTrap(std::string name);
    ~ClapTrap();
    ClapTrap(const ClapTrap &ref);
    ClapTrap &operator=(const ClapTrap &ref);
    unsigned int rangedAttack(std::string const & target);
    unsigned int meleeAttack(std::string const & target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
    
    void show_status(void);

};

#endif

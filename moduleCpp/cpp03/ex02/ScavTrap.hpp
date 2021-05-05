#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{

public:
    ScavTrap();
    ScavTrap(std::string name);
    ~ScavTrap();
    ScavTrap(const ScavTrap &ref);
    ScavTrap &operator=(const ScavTrap &ref);
    void challengeNewcomer(void);

};

#endif

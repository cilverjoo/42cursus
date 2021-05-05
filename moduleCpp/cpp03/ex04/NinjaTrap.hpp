#ifndef NINJATRAP_HPP
# define NINJATRAP_HPP

#include <iostream>
#include <string>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class NinjaTrap : virtual public ClapTrap
{

public:
    NinjaTrap();
    NinjaTrap(std::string name);
    ~NinjaTrap();
    NinjaTrap(const NinjaTrap &ref);
    NinjaTrap &operator=(const NinjaTrap &ref);

	void   ninjaShoebox(const FragTrap &ref);
	void   ninjaShoebox(const ScavTrap &ref);
	void   ninjaShoebox(const NinjaTrap &ref);
	void   ninjaShoebox(const ClapTrap &ref);

};

#endif

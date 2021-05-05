#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{

public:
    FragTrap();
    FragTrap(std::string name);
    ~FragTrap();
    FragTrap(const FragTrap &copy);
    FragTrap &operator=(const FragTrap &ft);
    unsigned int vaulthunter_dot_exe(std::string const & target);

};

#endif

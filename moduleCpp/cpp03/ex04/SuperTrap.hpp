#ifndef SUPERTRAP_HPP
# define SUPERTRAP_HPP

# include "NinjaTrap.hpp"
# include "FragTrap.hpp"

class SuperTrap : public FragTrap, public NinjaTrap
{
public:
	SuperTrap();
	SuperTrap(std::string name);
	SuperTrap(const SuperTrap & ref);
	~SuperTrap();
	SuperTrap& operator=(const SuperTrap & ref);

	unsigned int	rangedAttack(std::string const &target);
	unsigned int	meleeAttack(std::string const &target); 
};

#endif

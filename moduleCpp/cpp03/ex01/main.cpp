#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int     main(void)
{
	ScavTrap	stranger("stranger");
	ScavTrap	doctor("doctor");
	ScavTrap	phd(doctor);
    ScavTrap    steve;

	steve = stranger;
	steve.takeDamage(phd.rangedAttack(steve._name));

	phd.takeDamage(phd.meleeAttack(phd._name));

	steve.beRepaired(50);
	phd.beRepaired(100);

	for(int i = 0; i < 5; i++)
	{
		std::cout << i <<"\'st challenge! ";
		steve.challengeNewcomer();
	}
	return (0);
}

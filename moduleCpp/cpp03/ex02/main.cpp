#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int     main(void)
{
	ScavTrap	stranger("stranger");
	ScavTrap	doctor("doctor");
	ScavTrap	phd(doctor);
    ScavTrap    steve;
    FragTrap 	unknown;
    FragTrap 	ekim("ekim");
    FragTrap 	ekim2(ekim);

    unknown = FragTrap("bradpitt");
    ekim.takeDamage(unknown.rangedAttack(ekim._name));
    unknown.takeDamage(ekim2.meleeAttack(unknown._name));
    ekim.beRepaired(50);
    unknown.beRepaired(100);
    ekim.takeDamage(unknown.vaulthunter_dot_exe(ekim._name));

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

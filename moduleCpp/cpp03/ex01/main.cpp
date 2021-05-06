#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int     main(void)
{
	ScavTrap	stranger("stranger");
    ScavTrap    steve;
	ScavTrap	doctor("doctor");

	steve = stranger;
	steve.takeDamage(doctor.rangedAttack(steve._name));
	doctor.takeDamage(doctor.meleeAttack(doctor._name));

	steve.show_status();
	doctor.show_status();

	steve.beRepaired(10);
	doctor.beRepaired(20);
	
	steve.show_status();
	doctor.show_status();

	for(int i = 0; i < 5; i++)
	{
		std::cout << i <<"\'st challenge! " << std::endl;
		steve.challengeNewcomer();
	}
	return (0);
}

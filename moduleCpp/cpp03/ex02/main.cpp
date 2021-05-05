#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int     main(void)
{
	ScavTrap	stranger("stranger");
    FragTrap 	unknown;
    FragTrap 	ekim("ekim");

    unknown = FragTrap("bradpitt");

	ekim.show_status();
	unknown.show_status();
	stranger.show_status();

    ekim.takeDamage(unknown.rangedAttack(ekim._name));
	unknown.takeDamage(ekim.vaulthunter_dot_exe(unknown._name));
	stranger.takeDamage(unknown.vaulthunter_dot_exe(stranger._name));
	stranger.takeDamage(stranger.meleeAttack(stranger._name));
	
	ekim.show_status();
	unknown.show_status();
	stranger.show_status();
	
    ekim.beRepaired(20);
    unknown.beRepaired(10);
	
	ekim.show_status();
	unknown.show_status();

	for(int i = 0; i < 5; i++)
	{
		std::cout << i <<"\'st challenge! ";
		stranger.challengeNewcomer();
	}
	return (0);
}

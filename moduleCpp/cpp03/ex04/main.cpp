#include "NinjaTrap.hpp"
#include "SuperTrap.hpp"

int				main(void)
{
	NinjaTrap	Ninja("Ninja");
	ClapTrap	Ishikawa("Ishikawa");
	FragTrap	Hattori ("Hattori");
	ScavTrap	Jinichi("Jinichi");
	SuperTrap	samurai("samurai");
	SuperTrap	sinsen("sinsen");

	Ninja.ninjaShoebox(Ishikawa);
	Ninja.ninjaShoebox(Hattori);
	Ninja.ninjaShoebox(Jinichi);
	samurai.takeDamage(sinsen.meleeAttack(samurai._name));
	samurai.takeDamage(sinsen.rangedAttack(samurai._name));
	
	samurai.vaulthunter_dot_exe(sinsen._name);
	samurai.ninjaShoebox(Hattori);
	samurai.ninjaShoebox(Jinichi);
	
	return (0);
}

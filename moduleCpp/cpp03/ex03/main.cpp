#include "NinjaTrap.hpp"

int		main(void)
{
	NinjaTrap	Ninja("Ninja");
	ClapTrap    Ishikawa("Ishikawa");
	FragTrap    Hattori ("Hattori");
    ScavTrap    Jinichi("Jinichi");

	Ninja.ninjaShoebox(Ishikawa);
	Ninja.ninjaShoebox(Hattori);
	Ninja.ninjaShoebox(Jinichi);

	return (0);
}

#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

void	humanA_test(void)
{
	Weapon club = Weapon("crude spiked club");
	HumanA bob("Bob", club);
	bob.attack();
	club.setType("some other type of club");
	bob.attack();
	
}

void	humanB_test(void)
{
	Weapon club = Weapon("crude spiked club");
	HumanB jim("Jim");
	jim.setWeapon(club);
	jim.attack();
	club.setType("some other type of club");
	jim.attack();	
}

int main(void)
{
	humanA_test();
	humanB_test();
	return (0);
}

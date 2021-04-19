#include "ZombieHorde.hpp"

int				main(void)
{
	ZombieHorde	*horde;
	int			n;

	std::cin >> n;
	horde = new ZombieHorde(n);
	horde->makeZombies();
	delete horde;
	return (0);
}
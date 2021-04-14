#ifndef ZOMBIEHORDE_HPP
# define ZOMBIEHORDE_HPP

#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include "Zombie.hpp"

class ZombieHorde
{
	private:
		Zombie	*zombies;
		int		total;
		int		*randoms;

	public:
		ZombieHorde(int N);
		std::string returnRandomName(int idx);
		void		makeZombies(void);
		int			makeRandomNumber(void);
		~ZombieHorde();
};

#endif
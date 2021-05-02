#ifndef ZOMBIEEVENT_HPP
# define ZOMBIEEVENT_HPP

#include "Zombie.hpp"
#include <string>
#include <cstdlib>
#include <random>
#include <chrono>

class ZombieEvent
{
private:
	int			_eventType;

public:
	ZombieEvent();
	std::string	returnRandomName(int idx);
	void		setZombieType(int type);
	Zombie		*newZombie(std::string name);
	Zombie		*randomCrump(void);
	~ZombieEvent();
};



#endif

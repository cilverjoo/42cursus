/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:28:04 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/09 16:09:14 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieEvent.hpp"

ZombieEvent::ZombieEvent()
{
	_eventType = 0;
}

ZombieEvent::~ZombieEvent()
{
}

void		ZombieEvent::setZombieType(int type)
{
	_eventType = type;
}

std::string		returnRandomName(int idx)
{
	std::string names[20] = {"Trinidad", "Calista", "Brandi", "Patria", "Elma", 
	"Woodrow", "Jeannetta", "Janean", "Thanh", "Tyisha", "Mi", "Irvin", "Tillie", 
	"Teresa", "William", "Loyce", "Samatha", "Cherlyn", "Brad", "Blaine"};
	return (names[idx]);
}

Zombie		*ZombieEvent::newZombie(std::string Name)
{
	Zombie	*zombie;

	if (!(zombie = new Zombie()))
		return (0);
	zombie->setName(Name);
	zombie->setType(_eventType);
	return (zombie);
}


Zombie		*ZombieEvent::randomCrump(void)
{
	int		idx;
	Zombie	*zombie;

	idx = rand() % 20;	
	zombie = newZombie(returnRandomName(idx));
	zombie->announce();
	return (zombie);
}
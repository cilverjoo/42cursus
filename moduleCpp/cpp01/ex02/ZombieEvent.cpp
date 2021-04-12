/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:28:04 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/12 18:37:17 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieEvent.hpp"
#include "Zombie.hpp"

ZombieEvent::ZombieEvent()
{
	this->_eventType = 0;
}

ZombieEvent::~ZombieEvent()
{
}

void		ZombieEvent::setZombieType(int type)
{
	this->_eventType = type;
}

std::string		ZombieEvent::returnRandomName(int idx)
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
	std::string name;
	Zombie	*zombie;

	idx = rand() % 20;
	name = returnRandomName(idx);
	zombie = newZombie(name);
	zombie->announce();
	return (zombie);
}

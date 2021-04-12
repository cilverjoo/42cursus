/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:58:36 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/12 18:37:22 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
	std::cout << "A Zombie is deleted" << std::endl;
}

void		Zombie::setName(std::string Name)
{
	this->name = Name;
	return ;
}

void		Zombie::setType(int Type)
{
	this->type = Type;
	return ;
}

std::string	Zombie::getName(void)
{
	return (this->name);
}

int			Zombie::getType(void)
{
	return (this->type);
}

void		Zombie::announce(void)
{
	std::cout << "<" << Zombie::getName() << " (" << Zombie::getType() << ")> "
	 	<< "Braiiiiiiinnnssss..." << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pony.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:34 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/08 00:29:25 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pony.hpp"

Pony::Pony()
{
	this->color = "leopard";
	std::cout << "A " << color << "pony is here." << std::endl;
	return ;
}

Pony::~Pony(void)
{
	std::cout << "Pony is deleted." << std::endl;
	return ;	
}

Pony::walk(void)
{
	std::cout << "A Pony is walking around." << std::endl;
	return ;
}

void			Pony::run(void)
{
	std::cout << "A Pony is running :)" << std::endl;
	return ;
}

void			Pony::eat(void)
{
	std::cout << "A Pony is eating!" << std::endl;
	return ;
}

void			Pony::sleep(void)
{
	std::cout << "A Pony is sleeping..." << std::endl;
	return ;
}

std::string		Pony::getColor(void)
{
	return (this->color);
}

void			Pony::setColor(std::string color)
{
	this->color = color;
	return ;
}

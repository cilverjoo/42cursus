/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pony.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:34 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/12 17:00:32 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pony.hpp"

Pony::Pony()
{
	this->color = "leopard";
	std::cout << "A " << color << " pony is here." << std::endl;
	return ;
}

Pony::~Pony(void)
{
	std::cout << "Pony is deleted." << std::endl;
	return ;
}

void			Pony::walk(void)
{
	std::cout << "A " << this->color << " Pony is walking around." << std::endl;
	return ;
}

void			Pony::run(void)
{
	std::cout << "A " << this->color << " Pony is running :)" << std::endl;
	return ;
}

void			Pony::eat(void)
{
	std::cout << "A " << this->color << " Pony is eating!" << std::endl;
	return ;
}

void			Pony::sleep(void)
{
	std::cout << "A " << this->color << " Pony is sleeping..." << std::endl;
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

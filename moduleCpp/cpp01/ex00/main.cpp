/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:24:37 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/09 14:25:18 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pony.hpp"

void		PonyOnTheHeap(void)
{
	Pony	*pony;

	pony = new Pony();
	pony->setColor(std::string("white"));
	std::cout << pony->getColor() << std::endl;
	pony->walk();
	pony->run();
	pony->sleep();
	pony->eat();
	delete pony;
	return ;
}

void		PonyOnTheStack(void)
{
	Pony	pony;

	pony.setColor(std::string("Black"));
	std::cout << pony.getColor() << std::endl;
	pony.walk();
	pony.run();
	pony.sleep();
	pony.eat();
	return ;
}

int			main(void)
{
	std::cout << "call PonyOnTheHeap()" << std::endl;
	PonyOnTheHeap();
	std::cout << "PonyOnTheHeap() ended." << std::endl;
	std::cout << "======================" << std::endl;
	std::cout << "call PonyOnTheStack()" << std::endl;
	PonyOnTheStack();
	std::cout << "PonyOnTheStack() ended." << std::endl;
	return (0);
}
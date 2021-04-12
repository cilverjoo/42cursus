/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:33:51 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/09 16:20:46 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieEvent.hpp"
#include "Zombie.hpp"

int			main(void)
{
	ZombieEvent		event;
	Zombie			*zombie1;

	zombie1 = event.randomCrump();
	zombie1->announce();
	delete zombie1; 

	system("leaks zombie.out");
	return (0);
}
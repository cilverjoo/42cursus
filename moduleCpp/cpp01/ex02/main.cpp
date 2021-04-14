/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:33:51 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/14 11:32:43 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieEvent.hpp"
#include "Zombie.hpp"

int			main(void)
{
	ZombieEvent		event;
	Zombie			*zombie1;

	for (int i = 0; i < 10; i++)
	{
		zombie1 = event.randomCrump();
		delete zombie1;
	}
	return (0);
}

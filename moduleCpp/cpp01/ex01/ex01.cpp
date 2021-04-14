/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex01.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:36:07 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/12 17:04:56 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	memoryLeak(void)
{
	std::string* panther = new std::string("String panther");
	if (!panther)
		return ;
	std::cout << *panther << std::endl;
	delete panther;
}

void	memorySafe(void)
{
	std::string panther = std::string("String panther");
	std::cout << panther << std::endl;
}

int		main(void)
{
	memoryLeak();
	memorySafe();
	return (0);
}

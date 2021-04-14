/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:42:51 by ekim              #+#    #+#             */
/*   Updated: 2021/04/12 15:08:35 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>

int			main(int ac, char **av)
{
	int		i;
	int		j;
	
	i = 1;
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else if (ac > 1)
	{
		while (i < ac)
		{
			j = 0;
			while (j < strlen(av[i]))
				putchar(std::toupper(av[i][j++]));
			if (i != ac - 1)
				std::cout << " ";
			else
				std::cout << std::endl;
			i++;
		}
	}
	return (0);
}

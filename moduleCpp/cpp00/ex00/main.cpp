/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:55:11 by ekim              #+#    #+#             */
/*   Updated: 2021/04/07 17:56:05 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdio>
#include <string>

int			ft_isalpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int			main(int ac, char **av)
{
	int		i;
	size_t	len;
	size_t	j;
	std::string  change;
	
	i = 1;
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else if (ac > 1)
	{
		while (i < ac)
		{
			j = 0;
			len = strlen(av[i]);
			while (j < len)
			{
				if (ft_isalpha(av[i][j]))
					change += (av[i][j] - 32);
				else
					change += av[i][j];
				j++;
			}
			if (i != ac - 1)
				change += " ";
			i++;
		}
		std::cout << change << std::endl;
	}
	return (0);
}

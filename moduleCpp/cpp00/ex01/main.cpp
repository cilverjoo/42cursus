/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 00:28:52 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/07 01:17:51 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//phonebook에 8개 이상을 입력할 수 없다.

#include <iostream>
#include "phonebook.hpp"

int				main(void)
{
	PHONEBOOK	book;
	std::string	command;
	
	while (1)
	{
		std::cout << "Enter command : ";
		std::cin >> command;
		if (command == "ADD")
		{
			add_to_phonebook();
		}
		else if (command == "SEARCH")
		{
			search_from_phonebook();
		}
		else if (command == "EXIT")
		{
			std::cout << "Phonebook End..." << std::endl;
			break ;	
		}
		else
			std::cout << "Error: Incorrect command!" << std::endl;
	}
	return (0);
}
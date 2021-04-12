/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:09:41 by ekim              #+#    #+#             */
/*   Updated: 2021/04/12 19:14:46 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

int				main(void)
{
	Phonebook	book;
	std::string	command;
	int			idx;
	
	while (1)
	{
		if (!command.empty())
			command.clear();
		std::cout << "Enter command : ";
		std::cin >> command;
		if (command == "ADD")
			book.add_to_phonebook();
		else if (command == "SEARCH")
			book.search_from_phonebook();
		else if (command == "EXIT")
		{
			std::cout << "EXIT PHONEBOOK :)" << std::endl;
			break ;
		}
	}
	return (0);
}

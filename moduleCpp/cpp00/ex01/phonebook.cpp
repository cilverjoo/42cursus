/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:49:52 by ekim              #+#    #+#             */
/*   Updated: 2021/04/14 11:12:03 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"
# include <iostream>
# include <iomanip>
# include <string>

Phonebook::Phonebook()
{
	this->total = 0;
}

Phonebook::~Phonebook()
{
}

std::string		Phonebook::print_shortly(std::string str)
{
	std::string	tmp;
	
	if (str.length() > 10)
	{
		tmp = str.erase(9, str.length());
		tmp.append(".");
		return (tmp);
	}
	return (str);
}

void	Phonebook::show_phonebook(int index)
{
	std::cout << " --------------------------------------------------" << std::endl;	
	std::cout << "|   index   |  firstName |  lastName  |  nickName  |" << std::endl;
	std::cout << " --------------------------------------------------" << std::endl;
	if (index == 0)
	{
		for (int i = 0; i < this->total; i++)
		{
			std::cout << "|" << std::right << std::setw(10) << i + 1 << " | ";
			std::cout << std::right << std::setw(10) << print_shortly(this->contact[i].get_firstName()) << " | ";
			std::cout << std::right << std::setw(10) << print_shortly(this->contact[i].get_lastName()) << " | ";
			std::cout << std::right << std::setw(10) << print_shortly(this->contact[i].get_nickName()) << " | " << std::endl;
			std::cout << "---------------------------------------------------\n";
		}
	}
	else
	{
		std::cout << "|" << std::right << std::setw(10) << index << " | ";
		std::cout << std::right << std::setw(10) << print_shortly(this->contact[index - 1].get_firstName()) << " | ";
		std::cout << std::right << std::setw(10) << print_shortly(this->contact[index - 1].get_lastName()) << " | ";
		std::cout << std::right << std::setw(10) << print_shortly(this->contact[index - 1].get_nickName()) << " | " << std::endl;
		std::cout << "---------------------------------------------------\n";
	}
}

void			Phonebook::search_from_phonebook(void)
{
	int 		index;
	
	if (this->total == 0)
	{
		std::cout << "Add at least 1 contact!\n";
		return ;
	}
	show_phonebook(0);
	std::cout << "which index ? >> ";
	std::getline(std::cin, index);
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << "input is not a numeric (or int) value!\n";
		return ;
	}
	if (index <= 0 || index > this->total)
	{
		std::cout << "Error: Wrong range!\n";
		return ;
	}
	show_phonebook(index);
}

void			Phonebook::add_to_phonebook(void)
{
	std::string	str;
	
	if (this->total == 8)
	{
		std::cout << "Phonebook is already full! :(\n";
		return ;
	}
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "first name : ";
	std::cin >> str;
	this->contact[this->total].set_firstName(str);
	std::cout << "last name : ";
	std::cin >> str;
	this->contact[this->total].set_lastName(str);
	std::cout << "nick name : ";
	std::cin >> str;
	this->contact[this->total].set_nickName(str);
	std::cout << "login : ";
	std::cin >> str;
	this->contact[this->total].set_login(str);
	std::cout << "postal address : ";
	std::cin >> str;
	this->contact[this->total].set_postalAddress(str);
	std::cout << "email address : ";
	std::cin >> str;
	this->contact[this->total].set_emailAddress(str);
	std::cout << "phone number : ";
	std::cin >> str;
	this->contact[this->total].set_phoneNumber(str);
	std::cout << "birthday : ";
	std::cin >> str;
	this->contact[this->total].set_birthdayDate(str);
	std::cout << "favorite meal : ";
	std::cin >> str;
	this->contact[this->total].set_favoriteMeal(str);	
	std::cout << "underwear color : ";
	std::cin >> str;
	this->contact[this->total].set_underwearColor(str);
	std::cout << "darkest secret : ";
	std::cin >> str;
	this->contact[this->total].set_darkestSecret(str);
	std::cout << "A new contact is added to Phonebook!" << std::endl;
	std::cout << "---------------------------------------------------\n";
	this->total++;
}

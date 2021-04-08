/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:53:44 by ekim              #+#    #+#             */
/*   Updated: 2021/04/07 18:03:34 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"

void		Contact::set_firstName(std::string str)
{
	this->firstName = str;
	return ;
}

void		Contact::set_lastName(std::string str)
{
	this->lastName = str;
	return ;
}

void		Contact::set_nickName(std::string str)
{
	this->nickName = str;
	return ;
}

void		Contact::set_login(std::string str)
{
	this->login = str;
	return ;
}

void		Contact::set_postalAddress(std::string str)
{
	this->postalAddress = str;
	return ;
}

void		Contact::set_emailAddress(std::string str)
{
	this->emailAddress = str;
	return ;
}

void		Contact::set_phoneNumber(std::string str)
{
	this->phoneNumber = str;
	return ;
}

void		Contact::set_birthdayDate(std::string str)
{
	this->birthdayDate = str;
	return ;
}

void		Contact::set_favoriteMeal(std::string str)
{
	this->favoriteMeal = str;
	return ;
}

void		Contact::set_underwearColor(std::string str)
{
	this->underwearColor = str;
	return ;
}

void		Contact::set_darkestSecret(std::string str)
{
	this->darkestSecret = str;
	return ;
}

std::string Contact::get_firstName()
{
	return (this->firstName);
}

std::string Contact::get_lastName()
{
	return (this->lastName);
}

std::string Contact::get_nickName()
{
	return (this->nickName);
}

std::string Contact::get_login()
{
	return (this->login);
}

std::string Contact::get_postalAddress()
{
	return (this->postalAddress);
}

std::string Contact::get_emailAddress()
{
	return (this->emailAddress);
}

std::string Contact::get_phoneNumber()
{
	return (this->phoneNumber);
}

std::string Contact::get_birthdayDate()
{
	return (this->birthdayDate);
}

std::string Contact::get_favoriteMeal()
{
	return (this->nickName);
}

std::string Contact::get_underwearColor()
{
	return (this->nickName);
}

std::string Contact::get_darkestSecret()
{
	return (this->nickName);
}

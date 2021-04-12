/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:53:47 by ekim              #+#    #+#             */
/*   Updated: 2021/04/07 17:58:41 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>
#include <string>
#include <iomanip>

class	Contact
{

private:
	std::string firstName;
	std::string lastName;
	std::string nickName;
	std::string login;
	std::string postalAddress;
	std::string emailAddress;
	std::string phoneNumber;
	std::string birthdayDate;
	std::string favoriteMeal;
	std::string underwearColor;
	std::string darkestSecret;

public :
	void		set_firstName(std::string str);
	void		set_lastName(std::string str);
	void		set_nickName(std::string str);
	void		set_login(std::string str);
	void		set_postalAddress(std::string str);
	void		set_emailAddress(std::string str);
	void		set_phoneNumber(std::string str);
	void		set_birthdayDate(std::string str);
	void		set_favoriteMeal(std::string str);
	void		set_underwearColor(std::string str);
	void		set_darkestSecret(std::string str);
	std::string get_firstName();
	std::string get_lastName();
	std::string get_nickName();
	std::string get_login();
	std::string get_postalAddress();
	std::string get_emailAddress();
	std::string get_phoneNumber();
	std::string get_birthdayDate();
	std::string get_favoriteMeal();
	std::string get_underwearColor();
	std::string get_darkestSecret();

};

#endif

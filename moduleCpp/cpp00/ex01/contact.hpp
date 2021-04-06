#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>
#include <string>

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

	void		show_phonebook();
	void		show_desired();
	void		set_firstName(std::string str);
	void		set_lastname();
	void		set_nickname();
	void		set_login();
	void		set_postalAddress();
	void		set_emailAddress();
	void		set_phoneNumber();
	void		set_birthdayDate();
	void		set_favoriteMeal();
	void		set_underwearColor();
	void		set_darkestSecret();
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
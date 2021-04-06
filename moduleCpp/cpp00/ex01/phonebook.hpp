#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "contact.hpp"

class		Phonebook
{

private:
	Contact	contact[8];
	int		total;

public:
	Phonebook();
	void	search_from_phonebook();
	void	add_to_phonebook();
	void	show_desired();
	void	show_phonebook();
	~Phonebook();

};

#endif 

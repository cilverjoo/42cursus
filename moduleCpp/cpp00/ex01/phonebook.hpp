/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:53:58 by ekim              #+#    #+#             */
/*   Updated: 2021/04/07 14:01:52 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	void		show_phonebook(int index);
	void		search_from_phonebook(void);
	std::string	print_shortly(std::string str);
	void		add_to_phonebook();
	~Phonebook();
};

#endif 

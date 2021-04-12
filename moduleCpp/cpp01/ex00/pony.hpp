/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pony.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:11:01 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/09 14:25:40 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONY_HPP
# define PONY_HPP

#include <string>
#include <iostream>

class	Pony
{

private:
	std::string	color;

public:

	Pony(void);
	~Pony();

	void		walk(void);
	void		run(void);
	void		eat(void);
	void		sleep(void);
	std::string getColor(void);
	void		setColor(std::string color);

};

#endif
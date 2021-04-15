#ifndef HUMAN_HPP
# define HUMAN_HPP

#include "Brain.hpp"

class	Human
{
	private:
		const Brain 	brain;
		std::string		address;
		
	public:
		Human();
		~Human();
		const Brain		getBrain();
		std::string		identify();
};

#endif
 HumanA.cpp HumanA.hpp HumanB.cpp
HumanB.hpp main.cpp

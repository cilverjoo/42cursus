#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
	private:
		std::string	name;
		Weapon		*weapon;
		
	public:
		HumanB(std::string name);
		~HumanB();
		void		setWeapon(Weapon &club);
		void		setType(std::string type);
		void		attack();
};

#endif

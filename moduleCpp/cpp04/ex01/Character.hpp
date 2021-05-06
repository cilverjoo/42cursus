#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include <iostream>
#include <string>

#include "AWeapon.hpp"
#include "Enemy.hpp"

class Character
{
private:
	std::string _name;
	int _ap;
	AWeapon *_weapon;
	Character();
	
public:

	Character(std::string const & name);
	~Character();
	Character(const Character &ref);
	Character		&operator=(const Character &ref);
	void 			recoverAP(void);
	void 			equip(AWeapon *weapon);
	void 			attack(Enemy *enemy);
	std::string 	getName(void) const;
	int				getAP(void) const;
	AWeapon*		getWeapon() const;

};

std::ostream &operator<<(std::ostream &os, const Character &ref);

#endif

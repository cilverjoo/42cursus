#ifndef AWEAPON_HPP
# define AWEAPON_HPP

#include <iostream>
#include <string>

class AWeapon
{

protected:
	std::string _name;
	int			_apcost;
	int			_damage;

public:
	AWeapon();
	AWeapon(std::string const & name, int apcost, int damage);
	virtual ~AWeapon();
	AWeapon(const AWeapon &ref);
	AWeapon			&operator=(const AWeapon &ref);
	std::string		getName() const;
	int				getAPCost() const;
	int				getDamage() const;
	virtual void	attack() const = 0;

};

#endif

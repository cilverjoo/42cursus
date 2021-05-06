#ifndef PLASMARIFLE_HPP
# define PLASMARIFLE_HPP

#include <iostream>
#include <string>
#include "AWeapon.hpp"


class PlasmaRifle : public AWeapon
{

public:

	PlasmaRifle();
	~PlasmaRifle();
	PlasmaRifle(const PlasmaRifle &ref);
	PlasmaRifle &operator=(const PlasmaRifle &ref);
	virtual void attack() const;

};

#endif

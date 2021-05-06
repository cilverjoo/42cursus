#ifndef PowerFist_HPP
#define PowerFist_HPP

#include <iostream>
#include <string>
#include "AWeapon.hpp"

class PowerFist : public AWeapon
{

public:
	PowerFist();
	~PowerFist();
	PowerFist(const PowerFist &ref);
	PowerFist &operator=(const PowerFist &ref);
	virtual void attack() const;
};

#endif

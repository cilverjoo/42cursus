#ifndef RADSCORPION_HPP
# define RADSCORPION_HPP

#include <string>
#include <iostream>
#include "Enemy.hpp"

class RadScorpion : public Enemy
{

public:

	RadScorpion();
	~RadScorpion();
	RadScorpion(const RadScorpion &ref);
	RadScorpion &operator=(const RadScorpion &ref);
	virtual void	takeDamage(int);

};

#endif

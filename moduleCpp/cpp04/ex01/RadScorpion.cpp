#include "RadScorpion.hpp"

RadScorpion::RadScorpion() : Enemy(80, "RadScorpion")
{
	std::cout << "* click click click *" << std::endl;
}

RadScorpion::~RadScorpion()
{
	std::cout << "* SPROTCH *" << std::endl;
}

RadScorpion::RadScorpion(const RadScorpion &ref) : Enemy(ref)
{
	std::cout << "* click click click *" << std::endl;
}

RadScorpion 	&RadScorpion::operator=(const RadScorpion &ref)
{
	_hitPoint = ref._hitPoint;
	_type = ref._type;
	return (*this);
}

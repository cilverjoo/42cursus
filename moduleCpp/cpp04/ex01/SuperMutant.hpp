#ifndef SuperMutant_HPP
# define SuperMutant_HPP

#include <string>
#include <iostream>
#include "Enemy.hpp"

class SuperMutant : public Enemy
{

public:
	SuperMutant();
	~SuperMutant();
	SuperMutant(const SuperMutant &ref);
	SuperMutant &operator=(const SuperMutant &ref);

};

#endif

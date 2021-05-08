#include "SuperMutant.hpp"

SuperMutant::SuperMutant() : Enemy(170, "Super Mutant")
{
	std::cout << "Gaaah. Me want smash heads!" << std::endl;
}

SuperMutant::~SuperMutant()
{
	std::cout << "Aaargh..." << std::endl;
}

SuperMutant::SuperMutant(const SuperMutant &ref) : Enemy(ref)
{
	std::cout << "Gaaah. Me want smash heads!" << std::endl;
}
SuperMutant 			&SuperMutant::operator=(const SuperMutant &ref)
{
	_hitPoint = ref.getHP();
	_type = ref.getType();
	return (*this);
}

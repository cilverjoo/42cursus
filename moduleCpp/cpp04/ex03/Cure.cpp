#include "Cure.hpp"

Cure::Cure()
{
    std::cout << "Tactical Marine ready for battle!\n";
}

Cure::~Cure()
{
    std::cout << "Aaargh...\n";
}

Cure::Cure(const Cure &ref)
{
	*this = ref;
}

Cure         &Cure::operator=(const Cure &ref)
{
    (void)ref;
	return (*this);	
}

Cure*        Cure::clone() const
{
    return (new Cure(*this));
}

void        Cure::use(ICharacter& target)
{
    AMateria::use(target);
    std::cout << "* shoots an Cure bolt at " << target.getName() << "*\n";
}
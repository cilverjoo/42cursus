#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
}

Cure::~Cure()
{
}

Cure::Cure(const Cure &ref) : AMateria("cure")
{
	*this = ref;
}

Cure         &Cure::operator=(const Cure &ref)
{
    (void)ref;
	return (*this);	
}

AMateria*        Cure::clone() const
{
    return (new Cure(*this));
}

void        Cure::use(ICharacter& target)
{
    AMateria::use(target);
    std::cout << "* heals "<<target.getName()<<"’s wounds *\n";
}

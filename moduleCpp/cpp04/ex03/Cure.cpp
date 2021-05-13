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

Cure                &Cure::operator=(const Cure &ref)
{
    this->_xp = ref.getXP();
    this->_type = ref.getType();
	return (*this);	
}

AMateria*           Cure::clone() const
{
    Cure *clone = new Cure(*this);
    return (clone);
}

void                Cure::use(ICharacter& target)
{
    AMateria::use(target);
    std::cout << "* heals " << target.getName() << "’s wounds *\n";
}

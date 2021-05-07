#include "Ice.hpp"

Ice::Ice()
{
    std::cout << "Tactical Marine ready for battle!\n";
}

Ice::~Ice()
{
    std::cout << "Aaargh...\n";
}

Ice::Ice(const Ice &ref)
{
	*this = ref;
}

Ice         &Ice::operator=(const Ice &ref)
{
    (void)ref;
	return (*this);	
}

Ice*        Ice::clone() const
{
    return (new Ice(*this));
}

void        Ice::use(ICharacter& target)
{
    AMateria::use(target);
    std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
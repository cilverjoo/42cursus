#include "Ice.hpp"

Ice::Ice() : AMateria("ice")
{
}

Ice::~Ice()
{
}

Ice::Ice(const Ice &ref) : AMateria("ice")
{
	*this = ref;
}

Ice         &Ice::operator=(const Ice &ref)
{
    (void)ref;
	return (*this);	
}

AMateria*        Ice::clone() const
{
    return (new Ice(*this));
}

void        Ice::use(ICharacter& target)
{
    AMateria::use(target);
    std::cout <<  "* shoots an ice bolt at "<<target.getName()<<" *\n";
}

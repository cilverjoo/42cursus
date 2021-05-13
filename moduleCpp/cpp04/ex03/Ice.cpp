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

Ice                 &Ice::operator=(const Ice &ref)
{
    this->_xp = ref.getXP();
    this->_type = ref.getType();
	return (*this);	
}

AMateria*           Ice::clone() const
{
    Ice *clone = new Ice(*this);
    return (clone);
}

void                Ice::use(ICharacter& target)
{
    AMateria::use(target);
    std::cout <<  "* shoots an ice bolt at "<< target.getName() <<" *\n";
}

#include "AMateria.hpp"

AMateria::AMateria(std::string const & type) : _xp(0), _type(type)
{
}

AMateria::~AMateria()
{
    std::cout << "Aaargh...\n";
}

AMateria::AMateria(const AMateria &ref)
{
	*this = ref;
}

AMateria 			&AMateria::operator=(const AMateria &ref)
{
    this->_xp = ref._xp;
    this->_type = ref._type;
	return (*this);	
}

std::string const&	AMateria::getType() const
{
    return (this->_type);
}

unsigned int 		AMateria::getXP() const
{
    return (this->_xp);
}

void AMateria::use(ICharacter& target)
{
    (void)target;
    _xp += 10;
}
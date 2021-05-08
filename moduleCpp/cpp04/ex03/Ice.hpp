#ifndef ICE_HPP
# define ICE_HPP

#include <iostream>
#include <string>
#include "AMateria.hpp"
#include "ICharacter.hpp"

class Ice : public AMateria
{
public:
	Ice();
	~Ice();
	Ice(const Ice &ref);
	Ice &operator=(const Ice &ref);

    AMateria* clone() const;
    void use(ICharacter& target);

};

#endif

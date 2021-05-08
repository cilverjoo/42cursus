#ifndef AMATERIA_HPP
# define AMATERIA_HPP

#include <string>
#include <iostream>

#include "ICharacter.hpp"

class AMateria
{
protected:
    unsigned int    _xp;
    std::string     _type;
    AMateria();

public:
    AMateria(std::string const & type);
    virtual ~AMateria();
    AMateria(const AMateria &ref);
    AMateria& operator=(const AMateria &ref);
    std::string const & getType() const;
    unsigned int getXP() const;
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};

#endif

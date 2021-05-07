#ifndef CURE_HPP
# define CURE_HPP

#include <iostream>
#include <string>
#include "AMateria.hpp"
#include "ICharacter.hpp"

class CURE : public AMateria
{
private:

public:
	CURE();
	~CURE();
	CURE(const CURE &ref);
	CURE &operator=(const CURE &ref);

    AMateria* clone() const;
    void use(ICharacter& target);


};

#endif

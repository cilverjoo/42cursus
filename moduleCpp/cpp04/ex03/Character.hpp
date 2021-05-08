#ifndef Character_HPP
# define Character_HPP

#include <iostream>
#include <string>
#include "AMateria.hpp"

class Character : public ICharacter
{
private:
    std::string _name;
    AMateria*   _materia[4];
	int			_count;
	Character();

public:
    Character(std::string name);
	~Character();
	Character(const Character &ref);
	Character &operator=(const Character &ref);

	std::string const & getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);
};

#endif

#include "Character.hpp"

Character::Character(std::string name) : _name(name)
{
}

Character::~Character()
{
    std::cout << "Aaargh...\n";
}

Character::Character(const Character &ref)
{
	*this = ref;
}

Character         &Character::operator=(const Character &ref)
{
    (void)ref;
	return (*this);	
}

std::string const & Character::getName() const
{
    return (this->_name);
}

void Character::equip(AMateria* m)
{
    
}

void Character::unequip(int idx)
{

}

void Character::use(int idx, ICharacter& target)
{

}
#include "Character.hpp"

Character::Character(std::string name) : _name(name), _count(0)
{
    for (int i = 0; i < 4; i++)
        _materia[i] = NULL;
}

Character::~Character()
{
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

void Character::equip(AMateria* materia)
{
    if (_count < 4 && materia)
    {
        for (int i = 0; i < _count; i++)
        {
            if (_materia[i] == materia)
                return ;
        }
        _materia[_count] = materia;
        _count++;
    }
    return ;
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= _count)
        return ;
    delete _materia[idx];
    _materia[idx] = NULL;
    while (idx < 3)
    {
        _materia[idx] = _materia[idx + 1];
        idx++;
    }
    _materia[idx] = NULL;
    return ;
 }

void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx >= _count)
        return ;
    this->_materia[idx]->use(target);
}

#include "Character.hpp"

Character::Character(std::string name) : _name(name), _count(0)
{
    for (int i = 0; i < 4; i++)
        _materia[i] = NULL;
}

Character::~Character()
{
    for (int i = 0; i < this->_count; i++)
    {
        delete this->_materia[i];
        this->_materia[i] = NULL;
    }
}

Character::Character(const Character &ref)
{
	*this = ref;
}

Character         &Character::operator=(const Character &ref)
{
    for (int i = 0; i < this->_count; i++)
    {
        delete this->_materia[i];
        this->_materia[i] = NULL;
    }
    this->_name = ref.getName();
    this->_count = 0;
    for (int j = 0; j < ref._count; j++)
    {
        this->equip(ref._materia[j]->clone());
        this->_count++;
    }
	return (*this);
}

std::string const & Character::getName() const
{
    return (this->_name);
}

void Character::equip(AMateria* materia)
{
    if (this->_count < 4 && materia)
    {
        for (int i = 0; i < this->_count; i++)
        {
            if (this->_materia[i] == materia)
                return ;
        }
        this->_materia[_count++] = materia;
    }
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= this->_count || !this->_materia[idx])
        return ;
    this->_materia[idx] = NULL;
    while (idx < 3)
    {
        this->_materia[idx] = this->_materia[idx + 1];
        this->_materia[idx + 1] = NULL;
        idx++;
    }
    this->_count--;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx >= _count)
        return ;
    this->_materia[idx]->use(target);
}

int Character::getCount(void)
{
    return (this->_count);
}

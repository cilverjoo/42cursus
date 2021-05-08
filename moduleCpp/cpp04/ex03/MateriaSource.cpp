#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : _count(0)
{
	for (int i = 0; i < 4; i++)
        _materia[i] = NULL;
}

MateriaSource::~MateriaSource()
{
}

MateriaSource::MateriaSource(const MateriaSource &ref)
{
	*this = ref;
}

MateriaSource		&MateriaSource::operator=(const MateriaSource &ref)
{
    (void)ref;
	return (*this);	
}

void				MateriaSource::learnMateria(AMateria* materia)
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
}

AMateria*			MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < _count; i++)
	{
		if (this->_materia[i]->getType() ==  type)
			return (this->_materia[i]->clone());
	}
	return (0);
}

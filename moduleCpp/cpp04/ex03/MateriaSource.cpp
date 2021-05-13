#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : _count(0)
{
	for (int i = 0; i < 4; i++)
        this->_materia[i] = NULL;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		delete this->_materia[i];
        this->_materia[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource &ref)
{
	*this = ref;
}

MateriaSource		&MateriaSource::operator=(const MateriaSource &ref)
{
	for (int i = 0; i < this->_count; i++)
	{
		delete this->_materia[i];
		this->_materia[i] = NULL;
	}
	for (int j = 0; j < ref._count; j++)
	{
		this->_materia[j] = ref._materia[j]->clone();
	}
	return (*this);	
}

void				MateriaSource::learnMateria(AMateria* materia)
{
	if (this->_count < 4 && materia)
	{
		for (int i = 0; i < this->_count; i++)
        {
            if (this->_materia[i] == materia)
                return ;
        }
		this->_materia[_count++] = materia->clone();
	}
}

AMateria*			MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < this->_count; i++)
	{
		if (this->_materia[i]->getType() ==  type)
			return (this->_materia[i]->clone());
	}
	return (0);
}

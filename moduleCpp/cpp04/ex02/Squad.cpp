#include "Squad.hpp"

Squad::Squad() : _units(nullptr), _count(0)
{
}

Squad::~Squad()
{
    if (_count > 0)
    {
        for (int i = 0; i < this->_count; i++)
            delete this->_units[i];
        delete this->_units;
    }
}

Squad::Squad(const Squad &ref)
{
	*this = ref;
}

Squad 			&Squad::operator=(const Squad &ref)
{
    if (this->_units)
    {
        for (int i = 0; i < this->_count; i++)
            delete this->_units[i];
        delete this->_units;        
    }
    *this = ref;
    for (int i = 0; i < ref.getCount(); i++)
        this->push(ref.getUnit(i)->clone());
	return (*this);	
}

int             Squad::getCount(void) const
{
    return (this->_count);
}

ISpaceMarine*   Squad::getUnit(int idx) const
{
    if (this->_count == 0 || idx < 0 || idx >= this->_count)
        return (NULL);
    return (this->_units[idx]);
}

int             Squad::push(ISpaceMarine* n_unit)
{
    if (!_units)
    {
        this->_units = new ISpaceMarine*[1];
        this->_units[0] = n_unit;
        this->_count = 1;
    }
    else
    {
		for (int i = 0; i < this->_count; i++)
			if (this->_units[i] == n_unit)
				return (this->_count);
        ISpaceMarine **pushed_unit = new ISpaceMarine*[_count + 1];
        for (int i = 0; i < _count; i++)
            pushed_unit[i] = this->_units[i];
        pushed_unit[_count] = n_unit;
        delete[] this->_units;
        this->_units = pushed_unit;
        this->_count++;
    }
    return (this->_count);
}

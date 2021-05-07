#ifndef SQUAD_HPP
# define SQUAD_HPP

#include <string>
#include <iostream>
#include "ISquad.hpp"
#include "ISpaceMarine.hpp"

class Squad : public ISquad
{
private:
    ISpaceMarine** _units;
    int            _count;

public:
	Squad();
	virtual ~Squad();
	Squad(const Squad &ref);
	Squad &operator=(const Squad &ref);

	int             getCount() const;
	ISpaceMarine*   getUnit(int idx) const;
	int             push(ISpaceMarine* n_unit);

};

#endif

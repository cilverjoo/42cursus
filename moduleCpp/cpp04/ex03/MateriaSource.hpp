#ifndef MateriaSource_HPP
# define MateriaSource_HPP

#include <iostream>
#include <string>
#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{

private:

public:
	MateriaSource();
	~MateriaSource();
	MateriaSource(const MateriaSource &ref);
	MateriaSource &operator=(const MateriaSource &ref);

	virtual ~IMateriaSource();
	void learnMateria(AMateria*);
	AMateria* createMateria(std::string const & type);

};

#endif

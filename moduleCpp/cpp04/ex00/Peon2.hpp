#ifndef PEON2_HPP
# define PEON2_HPP

#include <iostream>
#include <string>

#include "Victim.hpp"

class Peon2 : public Victim
{

public:

	Peon2();
	Peon2(std::string _name);
	~Peon2();
	Peon2(const Peon2 &ref);
	Peon2 &operator=(const Peon2 &ref);
	void    getPolymorphed() const;

};

#endif

#ifndef PEON_HPP
# define PEON_HPP

#include <iostream>
#include <string>

#include "Victim.hpp"

class Peon : public Victim
{
private:
	std::string name;

public:

	Peon();
	Peon(std::string _name);
	~Peon();
	Peon(const Peon &ref);
	Peon &operator=(const Peon &ref);
	void    getPolymorphed() const;
};

#endif

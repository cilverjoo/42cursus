#ifndef SORCERER_HPP
# define SORCERER_HPP

#include <iostream>
#include <string>
#include "Victim.hpp"

class Sorcerer
{
private:
	std::string name;
	std::string title;
	Sorcerer();

public:
	Sorcerer(std::string _name, std::string _title);
	~Sorcerer();
	Sorcerer(const Sorcerer &ref);
	Sorcerer &operator=(const Sorcerer &ref);
	std::string		getName() const;
	std::string		getTitle() const;
	void polymorph(Victim const &ref) const;

};

std::ostream&	operator<<(std::ostream &os, const Sorcerer &ref);

#endif

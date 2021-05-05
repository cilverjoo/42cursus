#ifndef VICTIM_HPP
# define VICTIM_HPP

#include <iostream>
#include <string>

class Victim
{

protected:
	std::string		name;
	
public:

	Victim();
	Victim(std::string _name);
	virtual ~Victim();
	Victim(const Victim &ref);
	Victim			&operator=(const Victim &ref);
	std::string		getName() const;
	virtual void	getPolymorphed() const;

};

#endif

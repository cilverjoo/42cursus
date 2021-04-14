#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie
{
private:
	std::string name;
	int			type;

public:

	Zombie();
	void		setName(std::string Name);
	void		setType(int Type);
	std::string	getName(void);
	int			getType(void);
	void		announce(void);
	~Zombie();
};

#endif
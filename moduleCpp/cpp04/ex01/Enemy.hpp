#ifndef ENEMY_HPP
# define ENEMY_HPP

#include <string>
#include <iostream>

class Enemy
{
protected:
	int _hitPoint;
	std::string _type;

public:
	Enemy();
	Enemy(int hp, std::string const & type);
	~Enemy();
	Enemy(const Enemy &ref);
	Enemy &operator=(const Enemy &ref);
	std::string		getType(void) const;
	int				getHP(void) const;
	void			setHP(int newHP);
	virtual void	takeDamage(int amount);

};

#endif

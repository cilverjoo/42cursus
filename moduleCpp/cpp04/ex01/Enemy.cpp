#include "Enemy.hpp"

Enemy::Enemy(int hp, std::string const & type) : _hitPoint(hp), _type(type)
{
}

Enemy::~Enemy()
{	
}

Enemy::Enemy(const Enemy &ref)
{
	*this = ref;
}
Enemy 			&Enemy::operator=(const Enemy &ref)
{
	_hitPoint = ref.getHP();
	_type = ref.getType();
	return (*this);	
}

std::string		Enemy::getType() const
{
	return (this->_type);
}

int				Enemy::getHP() const
{
	return (this->_hitPoint);
}

void			Enemy::setHP(int newHP)
{
	_hitPoint = newHP;
}

void			Enemy::takeDamage(int amount)
{
	if (amount - 3 > 0)
	{
		if (_hitPoint - (amount - 3) >= 0)
			_hitPoint -= (amount - 3);
		else
			_hitPoint = 0;
	}
}

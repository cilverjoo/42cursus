#include "Fixed.hpp"

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << "Destructor callled" << std::endl;
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed &Fixed::operator=(const Fixed &copy)
{
	_value = copy.getRawBits();
	std::cout << "Assignation operator called" << std::endl;
	return (*this);
}

Fixed::Fixed(int value)
{
	std::cout << "Int constructor called" << std::endl;
	_value = value << _bits;
}

Fixed::Fixed(float value)
{
	std::cout << "Float constructor called" << std::endl;
	_value = roundf(value * (1 << _bits));
}

void		Fixed::setRawBits(int const value)
{
	_value = value;
}

int			Fixed::getRawBits() const
{
	return (_value);
}

int			Fixed::toInt(void) const
{
	return (_value >> _bits);
}

float		Fixed::toFloat(void) const
{
	return ((float)_value / (1 << _bits));
}

std::ostream	&operator<<(std::ostream &os, const Fixed &fixed)
{
	return (os << fixed.toFloat());
}
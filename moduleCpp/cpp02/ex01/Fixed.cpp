#include "Fixed.hpp"

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
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

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &ref)
{
	std::cout << "Copy constructor called" << std::endl;
	_value = ref.getRawBits();
	*this = ref;
}

Fixed 			&Fixed::operator=(const Fixed &ref)
{
	std::cout << "Assignation operator called" << std::endl;
	_value = ref.getRawBits();
	return (*this);
}

void			Fixed::setRawBits(int const value)
{
	_value = value;
}

int				Fixed::getRawBits(void) const
{
	return (_value);
}

int				Fixed::toInt(void) const
{
	return (_value >> _bits);
}

float			Fixed::toFloat(void) const
{
	return ((float)_value / (1 << _bits));
}

std::ostream	&operator<<(std::ostream &os, const Fixed &ref)
{
	return (os << ref.toFloat());	
}

#include "Fixed.hpp"

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
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

Fixed &Fixed::operator=(const Fixed &ref)
{
	_value = ref.getRawBits();
	std::cout << "Assignation operator called" << std::endl;
	return (*this);
}

void		Fixed::setRawBits(int const value)
{
	_value = value;
}

int			Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}

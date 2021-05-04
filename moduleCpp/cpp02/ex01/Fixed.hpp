#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>

class Fixed
{

private :
	int					_value;
	static const int	_bits = 8;

public :

	Fixed();
	Fixed(int param);
	Fixed(float param);
	~Fixed();
	Fixed(const Fixed &ref);
	Fixed			&operator=(const Fixed &ref);
	void			setRawBits(int const value);
	int				getRawBits(void) const;
	int				toInt(void) const;
	float			toFloat(void) const;

};

std::ostream		&operator<<(std::ostream &os, const Fixed &ref);

#endif

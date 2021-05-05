#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <string>

class Fixed
{

private :
	int					_value;
	static const int	_bits = 8;

public :

	Fixed();
	Fixed(const Fixed &ref);
	Fixed&			operator=(const Fixed &ref);
	void			setRawBits(int const value);
	int				getRawBits(void) const;
	~Fixed();

};

#endif


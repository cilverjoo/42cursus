#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <string>

class Fixed
{

private :
	int					_value;
	static const int	_fixed = 8;

public :

	Fixed();
	Fixed(const Fixed &copy);
	Fixed&			operator=(const Fixed &fixed);
	void			setRawBits(int const value);
	int				getRawBits(void) const;
	~Fixed();

};

#endif


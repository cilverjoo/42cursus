#ifndef AWESOME_HPP
# define AWESOME_HPP

class Awesome
{
public:
	Awesome() : _n( 42 )
	{
		 return;
	}
	int get( void ) const { return this->_n; }
	private:
	int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs ) { o << rhs.get(); return o; }

template< typename T >
void print( T const & x ) { std::cout << x << std::endl; return; }

#endif

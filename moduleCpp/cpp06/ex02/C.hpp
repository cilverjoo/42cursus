#ifndef C_HPP
# define C_HPP

#include "Base.hpp"

class C : public Base
{
private:
	C(const C& ref);
	C& operator=(const C& ref);
	
public:
	C();
	virtual ~C();

};

#endif

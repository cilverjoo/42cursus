#ifndef A_HPP
# define A_HPP

#include "Base.hpp"

class A : public Base
{
private:
	A(const A& ref);
	A& operator=(const A& ref);
	
public:
	A();
	virtual ~A();

};

#endif

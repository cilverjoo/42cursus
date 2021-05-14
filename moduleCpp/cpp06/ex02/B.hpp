#ifndef B_HPP
# define B_HPP

#include "Base.hpp"

class B : public Base
{
private:
	B(const B& ref);
	B& operator=(const B& ref);
	
public:
	B();
	virtual ~B();

};

#endif

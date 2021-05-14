#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <unistd.h>
#include <iostream>

Base *generate(void)
{
	int r = rand() % 3;
	if (r == 0)
		return (new A);
	if (r == 1)
		return (new B);
	return (new C);
}

void identify_from_pointer(Base *p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A";
	else if (dynamic_cast<B*>(p))
		std::cout << "B";
	else if (dynamic_cast<C*>(p))
		std::cout << "C";
}

void identify_from_reference(Base &p)
{
	identify_from_pointer(&p);
}

int main(void)
{
	srand(time(NULL));

	for (int i = 0; i < 50; i++)
	{
		Base *base = generate();
		std::cout << "Test " << i << ": ";
		identify_from_pointer(base);
		std::cout << ", ";
		identify_from_reference(*base);
		std::cout << std::endl;
		delete base;
	}
	return (0);
}
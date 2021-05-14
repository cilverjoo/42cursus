#include <iostream>
#include "Data.hpp"

int main(void)
{
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		std::cout << "\ntest " << i << ": " << '\n';
        std::cout << "=========================\n";
		void *raw = serialize();
		Data *dt = deserialize(raw);
        std::cout << "=========================\n";
		std::cout << "s1 :\t" << dt->s1 << '\n';
		std::cout << "n :\t" << dt->n << '\n';
		std::cout << "s2 :\t" << dt->s2 << std::endl;
        std::cout << "=========================\n";

		delete static_cast<char*>(raw);
		delete dt;
	}

	return (0);
}

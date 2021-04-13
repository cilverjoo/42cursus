#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(int N)
{
	this->total = N;
}

ZombieHorde::~ZombieHorde()
{
	delete[] this->zombies;
	delete[] this->randoms;
	std::cout << this->total << " zombies are all deleted :)" << std::endl;
}

int				ZombieHorde::makeRandomNumber(void)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 19);
	this->randoms = new int[this->total];
	for (int i = 0; i < this->total; i++)
		this->randoms[i] = dis(gen);
}

std::string		ZombieHorde::returnRandomName(int idx)
{
	std::string names[20] = {"Trinidad", "Calista", "Brandi", "Patria", "Elma", 
	"Woodrow", "Jeannetta", "Janean", "Thanh", "Tyisha", "Mi", "Irvin", "Tillie", 
	"Teresa", "William", "Loyce", "Samatha", "Cherlyn", "Brad", "Blaine"};
	return (names[idx]);
}

void				ZombieHorde::makeZombies(void)
{
	this->zombies = new Zombie[this->total];
	makeRandomNumber();
	for (int i = 0; i < this->total; i++)
	{
		zombies[i].setType(this->randoms[i]);
		zombies[i].setName(returnRandomName(this->randoms[i]));
		zombies[i].announce();
	}
}

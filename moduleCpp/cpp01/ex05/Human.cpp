#include "Human.hpp"

Human::Human()
{
}

Human::~Human()
{
}

const Brain		Human::getBrain() 
{
	return (this->brain);
}

std::string		Human::identify()
{
	return (this->brain.identify());
}

#include "Brain.hpp"

Brain::Brain()
{
	std::stringstream	stream;
	
	stream << this;
	this->address = stream.str();
}

Brain::~Brain()
{
}

std::string		Brain::identify() const
{
	return (this->address);
}

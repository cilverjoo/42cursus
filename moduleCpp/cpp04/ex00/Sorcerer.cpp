#include "Sorcerer.hpp"

Sorcerer::Sorcerer(std::string _name, std::string _title)
{
	name = 	_name;
	title = _title;
	std::cout << name << ", " << title << ", is born!" << std::endl;	
}

Sorcerer::~Sorcerer()
{
	std::cout << name << ", "<< title << ", is dead. Consequences will never be the same!" << std::endl;
}

Sorcerer::Sorcerer(const Sorcerer &ref)
{
	name = ref.name;
	title = ref.title;
	std::cout << name << ", " << title << ", is born!" << std::endl;	
}

Sorcerer &Sorcerer::operator=(const Sorcerer &ref)
{
	name = ref.name;
	title = ref.title;
	std::cout << name << ", " << title << ", is born!" << std::endl;
	return (*this);
}

std::string		Sorcerer::getName() const
{
	return (this->name);
}

std::string		Sorcerer::getTitle() const
{
	return (this->title);
}

void Sorcerer::polymorph(Victim const &ref) const
{
	ref.getPolymorphed();
}

std::ostream	&operator<<(std::ostream &os, const Sorcerer &ref)
{
	os << "I am " << ref.getName() << ", "<< ref.getTitle() << ", and I like ponies!\n";
	return (os);
}

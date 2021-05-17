#include "mutantstack.hpp"

template <typename T>
MutantStack<T>::MutantStack()
{
}

template <typename T>
MutantStack<T>::~MutantStack()
{
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &ref)
{
}

template <typename T>
MutantStack<T>&					MutantStack<T>::operator=(const MutantStack<T> &ref)
{
	*this = MutantStack(ref);
	return (*this);
}

template <typename T>
typename MutantStack<T>::iterator	MutantStack<T>::begin(void)
{
	return (this->c.begin());
}

template <typename T>
typename MutantStack<T>::iterator	MutantStack<T>::end(void)
{
	return (this->c.end());
}

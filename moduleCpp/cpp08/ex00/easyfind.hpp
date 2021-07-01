#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

class TargetNotFoundException : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return ("Value not found!");
    }
};

template<typename T>
int easyfind(T &container, int value)
{
    typename T::iterator iter;

    iter = std::find(container.begin(), container.end(), value);
    if (iter == container.end())
        throw (TargetNotFoundException());
    return (*iter);
}

#endif

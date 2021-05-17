#ifndef EASYFIND_HPP
# define EASYFINDR_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

template<typename T>
int easyfind(T &container, int value)
{
    typename T::iterator iter;

    iter = std::find(container.begin(), container.end(), value);
    if (iter == container.end())
        throw (std::exception);
    return (*iter);
}

#endif

#ifndef ITER_HPP
# define ITER_HPP

#include <string>
#include <iostream>

template <typename T>
void func(T const &value)
{
    std::cout << value << std::endl;
}

template <typename T>
void iter(T *array, int length, void (*func)(T const &ref))
{
    for (int i = 0; i < length; i++)
        (*func)(array[i]);
}

#endif
#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <string>
#include <iostream>

template <typename T>
class Array
{
private:
    T               *array;
    unsigned int    len;

public:
    Array()
    {
        this->array = new T[0];
        this->len = 0;
        return ;
    }

    Array(unsigned int n)
    {
        this->array = new T[n];
        this->len = n;
        return ;
    }

    ~Array()
    {
        if (this->len != 0)
            delete[] this->array;
        return ;
    }

    Array(const Array &ref)
    {
        *this = ref;
        return ;
    }

    Array& operator=(const Array &ref)
    {
        this->len = ref.size();
        this->array = new T[ref.size()];
        for (size_t i = 0; i < ref.size(); i++)
            this->array[i] = ref.array[i];
        return (*this);
    }

    unsigned int size() const
    {
        return (this->len);
    }

    T& operator[](unsigned int index) const
    {
        if (index >= this->len || index < 0)
            throw (OutOfRangeException());
        return (this->array[index]);
    }

    class OutOfRangeException : public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return ("Wrong indexing : Out of Range");
        }
    };
};

#endif

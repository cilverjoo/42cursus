#ifndef CONVERTER_HPP
# define CONVERTER_HPP

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <cfloat>

class Converter
{
private:
    Converter();
    std::string _str;
    double      _numeric;

public:
    Converter(std::string value);
    ~Converter();
    Converter(const Converter &ref);
    Converter& operator=(const Converter &ref);

    std::string getStr(void) const;
    double      getNumeric(void) const;
    void        ConvertToChar(void) const;
    void        ConvertToInt(void) const;
    void        ConvertToFloat(void) const;
    void        ConvertToDouble(void) const;
    void        display(void);

    class ImpossibleToConvert: public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
    class ImpossibleToDisplay : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };

};

#endif
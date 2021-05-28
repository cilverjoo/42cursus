#include "Converter.hpp"

Converter::Converter(std::string str) : _str(str), _numeric(0)
{
    try
    {
        this->_numeric = std::stod(str);
    }
    catch(const std::exception& e)
    {
        std::cout << "Wrong Argument! :(\n";
    }   
}

Converter::~Converter()
{
}

Converter::Converter(const Converter &ref)
{
    *this = ref;
}

Converter& Converter::operator=(const Converter &ref)
{
    this->_numeric = ref.getNumeric();
    this->_str = ref.getStr();
    return (*this);
}

double     Converter::getNumeric(void) const
{
    return (this->_numeric);
}

std::string Converter::getStr(void) const
{
    return (this->_str);
}

void Converter::ConvertToChar(void) const
{
    double numeric = this->_numeric;
    int integer = static_cast<int>(numeric);
    if (this->_numeric - integer != 0)
        throw (ImpossibleToConvert());
    else if (integer < 32 || integer > 126)
        throw (ImpossibleToDisplay());
    else
        std::cout << "char: '" << static_cast<char>(integer) << "'\n";
}

void Converter::ConvertToInt(void) const
{
    if (std::isnan(_numeric) || std::isinf(_numeric))
        throw (ImpossibleToConvert());
    else if (_numeric < INT_MIN|| _numeric > INT_MAX)
        throw (ImpossibleToConvert());
    else
        std::cout << "int : " << static_cast<int>(_numeric) << std::endl;
}

void Converter::ConvertToFloat(void) const
{
    if (_numeric > FLT_MAX || _numeric < FLT_MIN)
        throw (ImpossibleToConvert());
    float num = static_cast<float>(_numeric);
    int integer = static_cast<int>(_numeric);
    std::cout << "float: " << num;
    if (num - integer == 0)
        std::cout << ".0f" << std::endl;
    else
        std::cout << "f" << std::endl;
}

void Converter::ConvertToDouble(void) const
{
    if (_numeric > DBL_MAX || _numeric < DBL_MIN)
        throw (ImpossibleToConvert());
    double num = static_cast<double>(_numeric);
    int integer = static_cast<int>(_numeric);
    std::cout << "double: " << num;
    if (num - integer == 0)
        std::cout << ".0";
    std::cout << std::endl;
}

const char* Converter::ImpossibleToDisplay::what() const throw()
{
    return ("Non displayable");
}

const char* Converter::ImpossibleToConvert::what() const throw()
{
    return ("impossible");
}

void        Converter::display(void)
{
    try
    {
        ConvertToChar();
    }
    catch(const std::exception& e)
    {
        std::cout << "char: " << e.what() << '\n';
    }

    try
    {
        ConvertToInt();
    }
    catch(const std::exception& e)
    {
        std::cout << "int: " << e.what() << '\n';
    }

    try
    {
        ConvertToFloat();
    }
    catch(const std::exception& e)
    {
        std::cout << "float: " << e.what() << '\n';
    }
    
    try
    {
        ConvertToDouble();
    }
    catch(const std::exception& e)
    {
        std::cout << "double : " << e.what() << '\n';
    }
}

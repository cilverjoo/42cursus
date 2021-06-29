#include "Converter.hpp"

Converter::Converter(std::string input)
{
    this->_numeric = atof(input.c_str());
}

Converter::~Converter()
{
}

Converter::Converter(const Converter &ref)
{
    *this = ref;
}

double      Converter::getNumeric(void) const
{
    return (this->_numeric);
}

Converter& Converter::operator=(const Converter &ref)
{
    if (this == &ref)
        return (*this);
    this->_numeric = ref.getNumeric();
    return (*this);
}

void Converter::ConvertToChar(void) const
{
    if (std::isinf(this->_numeric) || std::isnan(this->_numeric))
        throw (ImpossibleToConvert());
    int ivalue = static_cast<int>(this->_numeric);
    if (this->_numeric - ivalue != 0)
        throw (ImpossibleToConvert());
    else if (ivalue < 32 || ivalue > 126)
        throw (ImpossibleToDisplay());
    else
        std::cout << "char: '" << static_cast<char>(ivalue) << "'\n";
}

void Converter::ConvertToInt(void) const
{
    if (std::isinf(this->_numeric) || std::isnan(this->_numeric))
        throw (ImpossibleToConvert());
    else if (this->_numeric < std::numeric_limits<int>::min()
            ||this->_numeric > std::numeric_limits<int>::max())
        throw (ImpossibleToConvert());
    else
        std::cout << "int : " << static_cast<int>(_numeric) << std::endl;
}

void Converter::ConvertToFloat(void) const
{
    if (std::isnan(this->_numeric))
    {
        std::cout << "float: nanf\n";
        return ;
    }
    else if (std::isinf(this->_numeric))
    {
        if (this->_numeric > 0)
            std::cout << "float: +inff" << std::endl;
        else
            std::cout << "float: -inff" << std::endl;
        return ;
    }
    if (this->_numeric > std::numeric_limits<float>::max()
        || this->_numeric < std::numeric_limits<float>::lowest())
        throw (ImpossibleToConvert());
    float fvalue = static_cast<float>(_numeric);
    int ivalue = static_cast<int>(_numeric);
    std::cout << "float: " << fvalue;
    if (fvalue - ivalue == 0)
        std::cout << ".0f" << std::endl;
    else
        std::cout << "f" << std::endl;
}

void Converter::ConvertToDouble(void) const
{
    if (std::isnan(this->_numeric))
    {
        std::cout << "double: nan\n";
        return ;
    }
    else if (std::isinf(this->_numeric))
    {
        if (this->_numeric > 0)
            std::cout << "double: +inff" << std::endl;
        else
            std::cout << "double: -inff" << std::endl;
        return ;
    }
    double num = static_cast<double>(_numeric);
    int integer = static_cast<int>(_numeric);
    std::cout << "double: " << num;
    if (num - integer == 0)
        std::cout << ".0";
    std::cout << std::endl;
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

const char* Converter::ImpossibleToDisplay::what() const throw()
{
    return ("Non displayable");
}

const char* Converter::ImpossibleToConvert::what() const throw()
{
    return ("impossible");
}

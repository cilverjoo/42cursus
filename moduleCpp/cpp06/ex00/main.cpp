#include "Converter.hpp"

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cout << "Arguments error!\n";
        return (0);
    }
    std::string input = std::string(av[1]);
    try
    {
        Converter convert(input);
        convert.display();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return (0);
    }
    return (0);
}

#include "Data.hpp"

void* serialize(void)
{
    std::string alphanum = "0123456789 \
        abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t len = alphanum.length();
    char* raw = new char[20];

    srand(clock());
    std::cout << "s1 :\t";
    for (int i = 0; i < 8; i++)
    {
        raw[i] = alphanum[rand() % len];
        std::cout << raw[i];
    }
    std::cout << std::endl;
    int randInt = rand();
	*reinterpret_cast<int*>(raw + 8) = randInt;
    std::cout << "n :\t" << randInt << std::endl;
    std::cout << "s2 :\t";
    for (int i = 0; i < 8; i++)
    {
        raw[12 + i] = alphanum[rand() % len];
        std::cout << raw[12 + i];
    }
    std::cout << std::endl;
    return (reinterpret_cast<void*>(raw));
}

Data* deserialize(void *raw)
{
	Data *data = new Data;

	data->s1 = std::string(static_cast<char*>(raw), 8);
	data->n = *reinterpret_cast<int*>(static_cast<char*>(raw) + 8);
	data->s2 = std::string(static_cast<char*>(raw) + 12, 8);
	return (data);
}
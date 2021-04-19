#include <iostream>
#include <fstream>
#include <string>

int         replaceFiles(std::string readName, std::string s1, std::string s2)
{
    std::ifstream   readFile;
    std::string     tmp;
    std::string     str;
    std::ofstream   writeToFile;
    size_t          f_idx;

    readFile.open(readName);
    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
            std::getline(readFile, tmp);
            if (readFile.eof())
                break ;
            tmp.append("\n");
            str += tmp;
        }
    }
    readFile.close();

    f_idx = str.find(s1);
    while (f_idx != std::string::npos)
    {        
        str.replace(f_idx, s1.length(), s2);
        f_idx = str.find(s1);
    }

    tmp.clear();
    tmp += (readName + std::string(".replace"));
    writeToFile.open(tmp.c_str());
    if (writeToFile.is_open())
        writeToFile.write(str.c_str(), str.size());
    return (0);
}

int         main(int ac, char **av)
{
    if (ac == 4)
    {
        replaceFiles(std::string(av[1]), 
            std::string(av[2]), std::string(av[3]));
    }
    else
        std::cout << "Wrong arguments!" << std::endl;
    return (0);
}
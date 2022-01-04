#include <iostream>
#include <filesystem>
#include <string>

int main()
{

    std::string filename;
    std::cout << "type input file name : ";
    std::cin >> filename;
    std::filesystem::path filepath{filename};
    while (!std::filesystem::exists(filepath))
    {
        std::cout << "type proper filepath" << std::endl;
        std::cin >> filename;
        filepath = filename;
    }
    std::cout << "end";
}

#include <iostream>
#include <vector>

void print_2dvector(std::vector<std::vector<double>> &vec)
{
    for (const auto &row : vec)
    {
        for (const auto &elem : row)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}
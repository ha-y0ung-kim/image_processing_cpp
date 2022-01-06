#include <iostream>
#include <vector>
#include <algorithm>

int check_valid_input(int maxnum)
{
    double num;
    std::cin >> num;

    int n = 1;
    std::vector<int> v(maxnum);
    std::generate(v.begin(), v.end(), [&n]()
                  { return n++; });

    while (std::find(v.begin(), v.end(), num) == v.end())
    {
        std::cout << " type a valid number: ";
        std::cin >> num;
    }

    return num;
}
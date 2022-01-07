#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief check if the input value is valid
 * check if the user gave a proper integer input within a valid region
 * checks if the input is an integer, and within a given input.
 * if a wrong value is given, continues getting input from a user
 * @param maxval integer value of the maximum possible integer value
 * @return int valid input value got from the user
 */
int check_valid_input(int maxval)
{
    double userinputval;
    std::cin >> userinputval;

    int startval = 1;
    std::vector<int> v(maxval);
    std::generate(v.begin(), v.end(), [&startval]()
                  { return startval++; });

    while (std::find(v.begin(), v.end(), userinputval) == v.end())
    {
        std::cout << " type a valid number: ";
        std::cin >> userinputval;
    }
    return userinputval;
}
#include <iostream>

/**
 * @brief get an integer value of kernel size from the user
 * get an odd integer value from a user
 * checks if the value is odd, if the value is not odd, ask for a proper input value
 * @return integer kernel_size (if 3 is returned, a kernel of size 3 x 3 is created)
 */
int type_kernel_size()
{
    std::cout << "Type an odd integer value of kernel size : " << std::endl;
    int kernel_size;
    std::cin >> kernel_size;
    while (kernel_size % 2 != 1)
    {
        std::cout << "Type an odd integer : " << std::endl;
        std::cin >> kernel_size;
    }
    return kernel_size;
}
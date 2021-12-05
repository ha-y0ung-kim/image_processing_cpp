#include <iostream>
int type_kernel_size()
{
    /*
    get a user input of kernel size
    */
    std::cout << "Type kernel size : " << std::endl;
    int kernel_size;
    std::cin >> kernel_size;
    while (kernel_size % 2 != 1)
    {
        std::cout << "Type an odd number of kernel size : " << std::endl;
        std::cin >> kernel_size;
    }
    return kernel_size;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <memory>

#include "src/vectortypes.h"
#include "src/type_kernel_size.h"
#include "src/check_valid_input.h"

#include "src/classes/Image.h"
#include "src/classes/Filter.h"
#include "src/classes/filterset.h"

int main()
{
    std::string filename;
    std::cout << "type input file name : ";
    std::cin >> filename;
    std::filesystem::path filepath(filename);
    while (!std::filesystem::exists(filepath) ||
           (std::filesystem::path(filepath).extension() != ".png") &&
               (std::filesystem::path(filepath).extension() != ".jpeg"))
    {
        std::cout << " Error in finding image file " << std::endl;
        std::cout << "type input file name: ";
        std::cin >> filename;
        filepath = filename;
    }

    Image image(filename);

    std::cout << " select image modification method " << std::endl;
    std::cout << "Type (1) to blurr the image" << std::endl;
    std::cout << "Type (2) to detect edges" << std::endl;

    int num = check_valid_input(2);

    std::unique_ptr<Filter> filter;

    if (num == 1)
    {

        std::cout << "select filter type " << std::endl;
        std::cout << "Type (1) for Mean blurring" << std::endl;
        std::cout << "Type (2) for Gaussian blurring" << std::endl;

        int num1 = check_valid_input(2);

        int kernel_size = type_kernel_size();

        if (num1 == 1)
        {
            filter = std::make_unique<MeanBlur>(kernel_size);
        }
        else
        {
            std::cout << "Type gaussian variance : " << std::endl;
            double kernel_sigma;
            std::cin >> kernel_sigma;

            filter = std::make_unique<GaussianBlur>(kernel_size, kernel_sigma);
        }
    }
    else
    {
        image.img_to_greyscale();
        std::cout << "select filter type : " << std::endl;
        std::cout << "Type (1) for Laplacian filter" << std::endl;
        std::cout << "Type (2) for sobal filter in x direction" << std::endl;
        std::cout << "Type (3) for sobal filter in y direction" << std::endl;

        int num1 = check_valid_input(3);

        if (num1 == 1)
        {
            int kernel_size = type_kernel_size();
            filter = std::make_unique<Laplacian>(kernel_size);
        }

        else if (num1 == 2)
        {
            filter = std::make_unique<Sobal_x>(3);
        }
        else
        {
            filter = std::make_unique<Sobal_y>(3);
        }
    }
    filter->setfilter();
    image.convolution(*filter);

    std::cout << " select an output image extension " << std::endl;
    std::cout << "Type (1) for PNG" << std::endl;
    std::cout << "Type (2) for JPEG" << std::endl;

    int num2 = check_valid_input(2);

    if (num2 == 1)
    {
        image.export_image(FileType::PNG);
    }

    else
    {
        image.export_image(FileType::JPEG);
    }
}
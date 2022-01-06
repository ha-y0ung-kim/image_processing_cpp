
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <memory>

// #include "header_files/imageload.h"
// #include "header_files/convolution.h"
// #include "header_files/filters.h"
// #include "header_files/printvector.h"
// #include "header_files/vectoroperation.h"
#include "header_files/vectortypes.h"
#include "header_files/kernel_input.h"
// #include "header_files/3d_convolution.h"

#include "header_files/Image.h"
#include "header_files/Filter.h"
#include "header_files/filterset.h"

int main()
{
    std::string filename;
    std::cout << "type input file name : ";
    std::cin >> filename;
    std::filesystem::path filepath(filename);
    while (!std::filesystem::exists(filepath))
    {
        std::cout << " Error in finding image file " << std::endl;
        std::cout << "type input file name: " << std::endl;
        std::cin >> filename;
        filepath = filename;
    } // Fix it

    Image image(filename);

    std::cout << " select image modification method : " << std::endl;
    std::cout << "Type (1) to blurr the image" << std::endl;
    std::cout << "Type (2) to detect edges" << std::endl;

    int num;
    std::cin >> num;

    std::unique_ptr<Filter> filter;

    if (num == 1)
    {

        std::cout << "select filter type : " << std::endl;
        std::cout << "Type (1) for Mean blurring" << std::endl;
        std::cout << "Type (2) for Gaussian blurring" << std::endl;

        int num1;
        std::cin >> num1;

        int kernel_size = type_kernel_size();

        if (num1 == 1)
        {
            filter = std::make_unique<MeanBlur>(kernel_size);
        }
        else if (num1 == 2)
        {
            std::cout << "Type gaussian variance : " << std::endl;
            double kernel_sigma;
            std::cin >> kernel_sigma;

            filter = std::make_unique<GaussianBlur>(kernel_size, kernel_sigma);
        }
        else
        {
            std::cout << "type a valid number " << std::endl;
        }
    }
    else if (num == 2)
    {
        image.img_to_greyscale();
        std::cout << "select filter type : " << std::endl;
        std::cout << "Type (1) for Laplacian filter" << std::endl;
        std::cout << "Type (2) for sobal filter in x direction" << std::endl;
        std::cout << "Type (3) for sobal filter in y direction" << std::endl;

        int num1;
        std::cin >> num1;

        if (num1 == 1)
        {
            int kernel_size = type_kernel_size();
            filter = std::make_unique<Laplacian>(kernel_size);
        }

        else if (num1 == 2)
        {
            filter = std::make_unique<Sobal_x>(3);
        }
        else if (num1 == 3)
        {
            filter = std::make_unique<Sobal_y>(3);
        }
        else
        {
            std::cout << "type a valid number " << std::endl;
        }
    }
    else
    {
        std::cout << " type a valid number " << std::endl;
    }
    filter->setfilter();
    image.convolution(*filter, true);

    std::cout << " select an output image extension " << std::endl;
    std::cout << "Type (1) for PNG" << std::endl;
    std::cout << "Type (2) for JPEG" << std::endl;

    int num2;
    std::cin >> num2;

    if (num2 == 1)
    {
        image.export_image(FileType::PNG);
    }

    else if (num2 == 2)
    {
        image.export_image(FileType::JPEG);
    }
    else
    {
        std::cout << "type a valid number " << std::endl;
    }
}
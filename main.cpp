
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "header_files/imageload.h"
#include "header_files/convolution.h"
#include "header_files/filters.h"
#include "header_files/printvector.h"
#include "header_files/vectoroperation.h"
#include "header_files/vectortypes.h"
#include "header_files/kernel_input.h"
#include "header_files/3d_convolution.h"

int main()
{

    vector3d image = load_image();
    std::cout << "select filter type : " << std::endl;
    std::cout << "Type (1) for Mean blurring" << std::endl;
    std::cout << "Type (2) for Gaussian blurring" << std::endl;
    std::cout << "Type (3) for Laplacian edge detection" << std::endl;
    std::cout << "Type (4) for unsharp image" << std::endl;

    int num;
    std::cin >> num;

    if (num == 1)
    {
        int kernel_size = type_kernel_size();
        vector2dd mean_kern;
        mean_kern = mean_filter(kernel_size);
        vector3d averaged_image;
        averaged_image = convolution3d(image, mean_kern, false);
        export_image(averaged_image);
    }
    else if (num == 2)
    {
        int kernel_size = type_kernel_size();

        std::cout << "Type gaussian variance : " << std::endl;
        double kernel_sigma;
        std::cin >> kernel_sigma;
        vector2dd gaussian_kern;
        gaussian_kern = gaussian_filter(kernel_size, kernel_sigma);
        vector3d gaussian_image;
        gaussian_image = convolution3d(image, gaussian_kern, false);
        export_image(gaussian_image);
    }

    else if (num == 3)
    {
        int kernel_size = type_kernel_size();

        vector2dd laplacian_kern;
        laplacian_kern = laplacian_filter(kernel_size);
        vector3d laplacian_image;
        laplacian_image = convolution3d(image, laplacian_kern, true);
        export_image(laplacian_image);
    }

    else if (num == 4)
    {
        int kernel_size = type_kernel_size();

        vector2dd laplacian_kern;
        laplacian_kern = laplacian_filter(kernel_size);
        vector3d laplacian_image, unsharp_image;
        laplacian_image = convolution3d(image, laplacian_kern, true);
        unsharp_image = image + 0.3 * laplacian_image;
        export_image(unsharp_image);
    }

    // std::vector<std::vector<std::vector<uint8_t>>> edge_image_x, edge_image_y, edge_image;
    // std::vector<std::vector<double>> sobal_kernel;
    // sobal_kernel = sobal_filter_x();
    // print_2dvector(sobal_kernel);
    // edge_image_x = convolution(grey_image, sobal_kernel, true);
    // edge_image_y = convolution(grey_image, sobal_filter_y(), true);
}
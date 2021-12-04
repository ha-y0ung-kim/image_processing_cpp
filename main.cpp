
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "imageload.h"
#include "convolution.h"
#include "filters.h"
#include "printvector.h"
#include "vectoroperation.h"
#include "vectortypes.h"

int main()
{

    vector3d grey_image = open_image_as_greyscale();

    // int kernel_size = 11;
    // std::vector<std::vector<double>> mean_kern;
    // mean_kern = mean_filter(kernel_size);
    // // print_2dvector(mean_kern);
    // std::vector<std::vector<std::vector<uint8_t>>> averaged_image;
    // averaged_image = convolution(grey_image, mean_kern, false);

    // std::vector<std::vector<std::vector<uint8_t>>> edge_image_x, edge_image_y, edge_image;
    // std::vector<std::vector<double>> sobal_kernel;
    // sobal_kernel = sobal_filter_x();
    // print_2dvector(sobal_kernel);
    // edge_image_x = convolution(grey_image, sobal_kernel, true);
    // edge_image_y = convolution(grey_image, sobal_filter_y(), true);

    // int kernel_size = 21;
    // double kernel_sigma = 5;
    // std::vector<std::vector<double>> gaussian_kern;
    // gaussian_kern = gaussian_filter(kernel_size, kernel_sigma);
    // print_2dvector(gaussian_kern);

    // std::vector<std::vector<std::vector<uint8_t>>> gaussian_image;
    // gaussian_image = convolution(grey_image, gaussian_kern, false);

    // int kernel_size = 5;
    // std::vector<std::vector<double>> laplacian_kern;
    // laplacian_kern = laplacian_filter(kernel_size);
    // // print_2dvector(laplacian_kern);

    // std::vector<std::vector<std::vector<uint8_t>>> laplacian_image;
    // laplacian_image = convolution(grey_image, laplacian_kern, true);
    // std::vector<std::vector<std::vector<uint8_t>>> unsharp_image(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(1)));

    // unsharp_image = grey_image + 0.3 * laplacian_image;

    export_image(grey_image);
}
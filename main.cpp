
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "imageload.h"
#include "convolution.h"
#include "filters.h"

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

std::vector<std::vector<std::vector<uint8_t>>> operator+(const std::vector<std::vector<std::vector<uint8_t>>> &vec_a,
                                                         const std::vector<std::vector<std::vector<uint8_t>>> &vec_b)
{
    /*
     * Overload operator+ to allow addition of two double vectors
     * of the same size. The return value is another vector formed by
     * adding the corresponding elements of vec_a and vec_b.
     */

    assert(vec_a.size() == vec_b.size());
    int width = vec_a.size();
    int height = vec_a[0].size();
    int channel = vec_a[0][0].size();

    std::vector<std::vector<std::vector<uint8_t>>> vec_sum(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(channel)));

    for (auto i = 0; i < width; i++)
    {
        for (auto j = 0; j < height; j++)
        {
            for (auto k = 0; k < channel; k++)
            {
                vec_sum[i][j][k] = vec_a[i][j][k] + vec_b[i][j][k];
            }
        }
    }
    return vec_sum;
}

std::vector<std::vector<std::vector<uint8_t>>> operator*(const double &number,
                                                         const std::vector<std::vector<std::vector<uint8_t>>> &vec_a)
{
    int width = vec_a.size();
    int height = vec_a[0].size();
    int channel = vec_a[0][0].size();

    std::vector<std::vector<std::vector<uint8_t>>> vec_mul(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(channel)));

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < channel; k++)
            {
                vec_mul[i][j][k] = number * vec_a[i][j][k];
            }
        }
    }
    return vec_mul;
}

int main()
{
    std::string img_filename;
    std::cout << "type input file name : ";
    std::cin >> img_filename;

    std::vector<std::vector<std::vector<uint8_t>>> grey_image;
    grey_image = open_image_as_greyscale(img_filename);

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

    int kernel_size = 5;
    std::vector<std::vector<double>> laplacian_kern;
    laplacian_kern = laplacian_filter(kernel_size);
    // print_2dvector(laplacian_kern);

    std::vector<std::vector<std::vector<uint8_t>>> laplacian_image;
    laplacian_image = convolution(grey_image, laplacian_kern, true);
    // std::vector<std::vector<std::vector<uint8_t>>> unsharp_image(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(1)));

        // unsharp_image = grey_image + 0.3 * laplacian_image;

    export_image(laplacian_image);
}
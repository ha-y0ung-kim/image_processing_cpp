#include <vector>
#include <cmath>

#include "vectortypes.h"

vector2dd mean_filter(int kernel_size)
{
    /*
    create a mean filter of size (kernel_size * kernel_size)
    blurrs the image
    */
    double kernel_value = 1 / ((double)kernel_size * (double)kernel_size);
    vector2dd mean_kernel(kernel_size, std::vector<double>(kernel_size, kernel_value));
    return mean_kernel;
}

vector2dd sobal_filter_x()
{
    vector2dd sobal_kernel = {{1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0}};
    return sobal_kernel;
}

vector2dd sobal_filter_y()
{
    vector2dd sobal_kernel = {{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}};
    return sobal_kernel;
}

vector2dd laplacian_filter(int kernel_size)
{
    /*
    create a laplacian_filter of size (kernel_size * kernel_size)
    edge detection of an image
    */
    vector2dd laplacian_kernel(kernel_size, std::vector<double>(kernel_size, -1.0));
    laplacian_kernel[kernel_size / 2][kernel_size / 2] = kernel_size * kernel_size - 1;
    return laplacian_kernel;
}

vector2dd gaussian_filter(int kernel_size, double sigma)
{
    /*
    create a gaussian filter of size (kernel_size * kernel_size) and variance sigma
    blurrs the image
    */
    vector2dd gaussian_kernel(kernel_size, std::vector<double>(kernel_size, 0));
    double sum = 0.0;
    for (int i = 0; i < kernel_size; i++)
    {
        for (int j = 0; j < kernel_size; j++)
        {
            gaussian_kernel[i][j] = 1 / (2 * M_PI * sigma * sigma) * std::exp(-(i * i + j * j) / (2 * sigma * sigma));
            sum += gaussian_kernel[i][j];
        }
    }
    for (int i = 0; i < kernel_size; i++)
    {
        for (int j = 0; j < kernel_size; j++)
        {
            gaussian_kernel[i][j] /= sum; // Normalize the filter
        }
    }
    return gaussian_kernel;
}
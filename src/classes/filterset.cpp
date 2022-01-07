#include <vector>
#include <cmath>

#include "filterset.h"

MeanBlur::MeanBlur(int kernelsize)
{
    kernel_size = kernelsize;
}

void MeanBlur::setfilter()
{

    double kernel_value = 1 / ((double)kernel_size * (double)kernel_size);
    vector2dd mean_kernel(kernel_size, std::vector<double>(kernel_size, kernel_value));
    kernel = mean_kernel;
}

GaussianBlur::GaussianBlur(int kernelsize, double sigma)
    : _variance(sigma)
{
    kernel_size = kernelsize;
}

void GaussianBlur::setfilter()
{

    vector2dd gaussian_kernel(kernel_size, std::vector<double>(kernel_size, 0));
    double sum = 0.0;
    for (int i = 0; i < kernel_size; i++)
    {
        for (int j = 0; j < kernel_size; j++)
        {
            gaussian_kernel[i][j] = 1 / (2 * M_PI * _variance * _variance) * std::exp(-(i * i + j * j) / (2 * _variance * _variance));
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
    kernel = gaussian_kernel;
}

Laplacian::Laplacian(int kernelsize)
{
    kernel_size = kernelsize;
}

void Laplacian::setfilter()
{
    vector2dd laplacian_kernel(kernel_size, std::vector<double>(kernel_size, -1.0));
    laplacian_kernel[kernel_size / 2][kernel_size / 2] = kernel_size * kernel_size - 1;
    kernel = laplacian_kernel;
}

Sobal_x::Sobal_x(int kernelsize)
{
    kernel_size = kernelsize;
}

void Sobal_x::setfilter()
{
    vector2dd sobal_kernel = {{1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0}};
    kernel = sobal_kernel;
}

Sobal_y::Sobal_y(int kernelsize)
{
    kernel_size = kernelsize;
}

void Sobal_y::setfilter()
{
    vector2dd sobal_kernel = {{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}};
    kernel = sobal_kernel;
}
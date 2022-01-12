#include <vector>
#include <cmath>

#include "filterset.h"

MeanBlur::MeanBlur(const int kernelsize)
{
    kernel_size = kernelsize;
    neg_value = false;
}

void MeanBlur::set_filter()
{

    const double kernel_value = 1 / ((double)kernel_size * (double)kernel_size);
    kernel = vector2dd(kernel_size, std::vector<double>(kernel_size, kernel_value));
}

GaussianBlur::GaussianBlur(const int kernelsize, const double sigma)
    : _variance(sigma)
{
    kernel_size = kernelsize;
    neg_value = false;
}

void GaussianBlur::set_filter()
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

Laplacian::Laplacian(const int kernelsize)
{
    kernel_size = kernelsize;
    neg_value = true;
}

void Laplacian::set_filter()
{
    vector2dd laplacian_kernel(kernel_size, std::vector<double>(kernel_size, -1.0));
    laplacian_kernel[kernel_size / 2][kernel_size / 2] = kernel_size * kernel_size - 1;
    kernel = laplacian_kernel;
}

Sobal_x::Sobal_x(const int kernelsize)
{
    kernel_size = kernelsize;
    neg_value = true;
}

void Sobal_x::set_filter()
{
    kernel = vector2dd{{1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0}};
}

Sobal_y::Sobal_y(const int kernelsize)
{
    kernel_size = kernelsize;
    neg_value = true;
}

void Sobal_y::set_filter()
{
    kernel = vector2dd{{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}};
}

Robert_Cross_x::Robert_Cross_x(const int kernelsize)
{
    kernel_size = kernelsize;
    neg_value = true;
}

void Robert_Cross_x::set_filter()
{
    kernel = vector2dd{{1.0, 0.0}, {0.0, -1.0}};
}

Robert_Cross_y::Robert_Cross_y(const int kernelsize)
{
    kernel_size = kernelsize;
    neg_value = true;
}

void Robert_Cross_y::set_filter()
{
    kernel = vector2dd{{0.0, 1.0}, {-1.0, 0.0}};
}
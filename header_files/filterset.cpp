#include <vector>
#include <cmath>

#include "filterset.h"

MeanBlur::MeanBlur(int kernelsize)
{
    _kernel_size = kernelsize;
}

void MeanBlur::setfilter()
{

    double kernel_value = 1 / ((double)_kernel_size * (double)_kernel_size);
    vector2dd mean_kernel(_kernel_size, std::vector<double>(_kernel_size, kernel_value));
    _kernel = mean_kernel;
}

GaussianBlur::GaussianBlur(int kernelsize, double sigma)
    : _variance(sigma)
{
    _kernel_size = kernelsize;
}

void GaussianBlur::setfilter()
{
    /*
    create a gaussian filter of size (kernel_size * kernel_size) and variance sigma
    blurrs the image
    */
    vector2dd gaussian_kernel(_kernel_size, std::vector<double>(_kernel_size, 0));
    double sum = 0.0;
    for (int i = 0; i < _kernel_size; i++)
    {
        for (int j = 0; j < _kernel_size; j++)
        {
            gaussian_kernel[i][j] = 1 / (2 * M_PI * _variance * _variance) * std::exp(-(i * i + j * j) / (2 * _variance * _variance));
            sum += gaussian_kernel[i][j];
        }
    }
    for (int i = 0; i < _kernel_size; i++)
    {
        for (int j = 0; j < _kernel_size; j++)
        {
            gaussian_kernel[i][j] /= sum; // Normalize the filter
        }
    }
    _kernel = gaussian_kernel;
}

Laplacian::Laplacian(int kernelsize)
{
    _kernel_size = kernelsize;
}

void Laplacian::setfilter()
{
    /*
    create a laplacian_filter of size (kernel_size * kernel_size)
    edge detection of an image
    */
    vector2dd laplacian_kernel(_kernel_size, std::vector<double>(_kernel_size, -1.0));
    laplacian_kernel[_kernel_size / 2][_kernel_size / 2] = _kernel_size * _kernel_size - 1;
    _kernel = laplacian_kernel;
}

Sobal_x::Sobal_x()
{
    _kernel_size = 3;
}

void Sobal_x::setfilter()
{
    vector2dd sobal_kernel = {{1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0}};
    _kernel = sobal_kernel;
}

Sobal_y::Sobal_y()
{
    _kernel_size = 3;
}

void Sobal_y::setfilter()
{
    vector2dd sobal_kernel = {{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}};
    _kernel = sobal_kernel;
}
#include <vector>
#include <cmath>

std::vector<std::vector<double>> mean_filter(int kernel_size)
{
    double kernel_value = 1 / ((double)kernel_size * (double)kernel_size);
    std::vector<std::vector<double>> mean_kernel(kernel_size, std::vector<double>(kernel_size, kernel_value));
    return mean_kernel;
}

std::vector<std::vector<double>> sobal_filter_x()
{
    std::vector<std::vector<double>> sobal_kernel = {{1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0}};
    return sobal_kernel;
}

std::vector<std::vector<double>> sobal_filter_y()
{
    std::vector<std::vector<double>> sobal_kernel = {{1.0, 2.0, 1.0}, {0.0, 0.0, 0.0}, {-1.0, -2.0, -1.0}};
    return sobal_kernel;
}

std::vector<std::vector<double>> laplacian_filter(int kernel_size)
{
    std::vector<std::vector<double>> laplacian_kernel(kernel_size, std::vector<double>(kernel_size, -1.0));
    laplacian_kernel[kernel_size / 2][kernel_size / 2] = kernel_size * kernel_size - 1;
    return laplacian_kernel;
}

std::vector<std::vector<double>> gaussian_filter(int kernel_size, double sigma)
{
    std::vector<std::vector<double>> gaussian_kernel(kernel_size, std::vector<double>(kernel_size, 0));
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
            gaussian_kernel[i][j] /= sum;
        }
    }
    return gaussian_kernel;
}
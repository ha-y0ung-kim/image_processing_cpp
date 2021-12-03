
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

std::vector<std::vector<std::vector<uint8_t>>> load_image(std::string filename)
{
    const char *img_filename = filename.c_str();
    int width, height, channels;
    uint8_t *img = stbi_load(img_filename, &width, &height, &channels, 0);
    if (img == NULL)
    {
        std::cout << "Error in loading the image" << std::endl;
        exit(1);
    }
    std::cout << "Loaded image"
              << "width : " << width << ",  height : " << height
              << ", number of channels : " << channels << std::endl;

    std::vector<std::vector<std::vector<uint8_t>>> image(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(channels)));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < channels; k++)
            {
                image[i][j][k] = *(img + (i + width * j) * channels + k);
            }
        }
    }
    stbi_image_free(img);
    return image;
}

void export_image(std::vector<std::vector<std::vector<uint8_t>>> image)
{
    int width = image.size();
    int height = image[0].size();
    int channels = image[0][0].size();

    uint8_t out[width * height * channels] = {0};

    int a = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < channels; k++)
            {
                out[a] = image[j][i][k];
                a += 1;
            }
        }
    }

    uint8_t *final_img;
    final_img = out;

    stbi_write_png("test.png", width, height, channels, final_img, width * channels);
}

std::vector<std::vector<std::vector<uint8_t>>> img_to_greyscale(std::vector<std::vector<std::vector<uint8_t>>> image)
{
    int width = image.size();
    int height = image[0].size();
    int channel = image[0][0].size();
    std::vector<std::vector<std::vector<uint8_t>>> grey_image(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(1)));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < channel; k++)
            {
                grey_image[i][j][0] += image[i][j][k] / 3;
            }
        }
    }
    return grey_image;
}

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

std::vector<std::vector<std::vector<uint8_t>>> convolution(std::vector<std::vector<std::vector<uint8_t>>> image, std::vector<std::vector<double>> kernel)
{
    int width = image.size();
    int height = image[0].size();
    std::vector<std::vector<std::vector<uint8_t>>> output_image(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(1)));

    int kernel_width = kernel.size();
    int kernel_height = kernel[0].size();
    int mm, nn, ii, jj;

    double val;
    int y, x;

    // for (int i = 0; i < width; i++)
    // {
    //     for (int j = 0; j < height; j++)
    //     {
    //         val = 0.0;
    //         for (int m = 0; m < kernel_width; m++)
    //         {
    //             mm = kernel_width - 1 - m;
    //             for (int n = 0; n < kernel_height; n++)
    //             {
    //                 nn = kernel_height - 1 - n;

    //                 ii = i + kernel_width / 2 - mm;
    //                 jj = j + kernel_height / 2 - nn;

    //                 if (ii >= 0 & ii < width & jj >= 0 & jj < height)
    //                 {
    //                     val += (double)image[ii][jj][0] * kernel[mm][nn];
    //                 }
    //             }
    //         }
    //         val += 128;
    //         //std::cout << val << " ";
    //         if (val < 0)
    //         {
    //             output_image[i][j][0] = 0;
    //         }
    //         else if (val > 255)
    //         {
    //             output_image[i][j][0] = 255;
    //         }
    //         else
    //         {
    //             output_image[i][j][0] = val;
    //         }
    //     }
    // }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            val = 0.0;
            for (int k = 0; k < kernel_height; k++)
            {
                for (int l = 0; l < kernel_width; l++)
                {
                    x = (j - kernel_width / 2 + l + width) % width;
                    y = (i - kernel_height / 2 + k + height) % height;
                    val += (double)image[y][x][0] * kernel[l][k];
                }
            }
            val += 128;
            if (val < 0)
            {
                output_image[i][j][0] = 0;
            }
            else if (val > 255)
            {
                output_image[i][j][0] = 255;
            }
            else
            {
                output_image[i][j][0] = val;
            }
        }
    }
    return output_image;
}

int main()
{
    std::string img_filename;
    std::cout << "type input file name : ";
    std::cin >> img_filename;

    std::vector<std::vector<std::vector<uint8_t>>> image;
    image = load_image(img_filename);

    int width = image.size();
    int height = image[0].size();
    std::vector<std::vector<std::vector<uint8_t>>> grey_image;
    grey_image = img_to_greyscale(image);

    // int kernel_size = 5;
    // std::vector<std::vector<double>> mean_kern;
    // mean_kern = mean_filter(kernel_size);
    // print_2dvector(mean_kern);

    // std::vector<std::vector<std::vector<uint8_t>>> averaged_image;
    // averaged_image = convolution(grey_image, mean_kern);

    std::vector<std::vector<std::vector<uint8_t>>> edge_image_x, edge_image_y, edge_image;
    std::vector<std::vector<double>> sobal_kernel;
    sobal_kernel = sobal_filter_x();
    print_2dvector(sobal_kernel);
    edge_image_x = convolution(grey_image, sobal_kernel);
    edge_image_y = convolution(grey_image, sobal_filter_y());

    export_image(edge_image_x);
}
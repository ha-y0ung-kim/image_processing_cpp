
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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

int main()
{
    std::string img_filename;
    std::cout << "type input file name ";
    std::cin >> img_filename;

    std::vector<std::vector<std::vector<uint8_t>>> image;
    image = load_image(img_filename);

    int width = image.size();
    int height = image[0].size();
    std::vector<std::vector<std::vector<uint8_t>>> grey_image;
    grey_image = img_to_greyscale(image);

    std::vector<std::vector<double>> mean_kern;
    mean_kern = mean_filter(3);
    print_2dvector(mean_kern);

    export_image(grey_image);
}
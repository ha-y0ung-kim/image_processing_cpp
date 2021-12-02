
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

std::vector<std::vector<std::vector<uint8_t>>> convolution(std::vector<std::vector<std::vector<uint8_t>>> image, std::vector<std::vector<std::vector<uint8_t>>> kernel)
{
}

std::vector<std::vector<std::vector<uint8_t>>> mean_filter(int kernal_size, int num_channel)
{
    double kernal_value = 1 / (kernal_size * kernal_size);
    std::vector<std::vector<std::vector<uint8_t>>> output(kernal_size, std::vector<std::vector<uint8_t>>(kernal_size, std::vector<uint8_t>(num_channel)));
    std::fill(output.begin(), output.end(), kernal_value);
    return output;
}

void print_3dmatrix(std::vector<std::vector<std::vector<uint8_t>>> &vec)
{
    // print 3d matrix vec

    for (int i = 0; i < vec[0][0].size(); i++)
    {
        for (int j = 0; j < vec[1].size(); j++)
        {
            for (int k = 0; k < vec.size(); k++)
            {
                std::cout << vec[k][j][i] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

int main()
{
    std::string img_filename;
    std::cout << "type input file name";
    std::cin >> img_filename;
    const char *filename = img_filename.c_str();

    int width, height, channels;
    uint8_t *img = stbi_load(filename, &width, &height, &channels, 0);

    //uint8_t *img = stbi_load("img_lenna.png", &width, &height, &channels, 0);

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
    stbi_image_free(img);
}
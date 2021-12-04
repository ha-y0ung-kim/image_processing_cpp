#include <iostream>
#include <vector>
#include <string>

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

    std::vector<std::vector<std::vector<uint8_t>>> image(channels, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(width)));

    for (int k = 0; k < channels; k++)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[k][i][j] = *(img + (j + width * i) * channels + k);
            }
        }
    }
    stbi_image_free(img);
    return image;
}

void export_image(std::vector<std::vector<std::vector<uint8_t>>> image)
{
    int channels = image.size();
    int height = image[0].size();
    int width = image[0][0].size();

    uint8_t out[width * height * channels] = {0};

    int a = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < channels; k++)
            {
                out[a] = image[k][i][j];
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
    int num_channels = image.size();
    int height = image[0].size();
    int width = image[0][0].size();

    std::vector<std::vector<std::vector<uint8_t>>> grey_image(1, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(width)));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < num_channels; k++)
            {
                grey_image[0][i][j] += image[k][i][j] / 3;
            }
        }
    }
    return grey_image;
}

std::vector<std::vector<std::vector<uint8_t>>> open_image_as_greyscale(std::string filename)
{
    std::vector<std::vector<std::vector<uint8_t>>> image, grey_image;
    image = load_image(filename);
    grey_image = img_to_greyscale(image);
    return grey_image;
}
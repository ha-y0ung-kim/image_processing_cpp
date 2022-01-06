#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include "vectortypes.h"
#include "Image.h"

Image::Image(std::string filepath) : _path(filepath)
{
    const char *img_filename = filepath.c_str();
    int width, height, num_channels;

    uint8_t *img = stbi_load(img_filename, &width, &height, &num_channels, 3);
    std::cout << "Loaded image"
              << "width : " << width << ",  height : " << height
              << ", number of channels : " << num_channels << std::endl;

    vector3d image(num_channels, vector2d(height, std::vector<uint8_t>(width)));

    for (int k = 0; k < num_channels; k++)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                image[k][i][j] = *(img + (j + width * i) * num_channels + k);
            }
        }
    }
    _vec = image;

    stbi_image_free(img);
}

Image::Image(vector3d imgvec) : _vec(imgvec)
{
}

void Image::img_to_greyscale()
{
    int num_channels = _vec.size();
    int height = _vec[0].size();
    int width = _vec[0][0].size();

    vector3d grey_image(1, vector2d(height, std::vector<uint8_t>(width)));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < num_channels; k++)
            {
                grey_image[0][i][j] += _vec[k][i][j] / 3;
            }
        }
    }
    _vec = grey_image;
}

void Image::export_image(FileType filetype)
{
    /*
    export an image into a .PNG file
    input
        image : image to be exported
    */
    int num_channels = _vec.size();
    int height = _vec[0].size();
    int width = _vec[0][0].size();

    uint8_t out[width * height * num_channels] = {0};

    int a = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < num_channels; k++)
            {
                out[a] = _vec[k][i][j];
                a += 1;
            }
        }
    }

    uint8_t *final_img;
    final_img = out;
    if (filetype == FileType::PNG)
    {
        stbi_write_png("output.png", width, height, num_channels, final_img, width * num_channels);
    }
    else if (filetype == FileType::PNG)
    {
        stbi_write_jpg("output.jpeg", width, height, num_channels, final_img, width * num_channels);
    }
    else
    {
        std::cout << "invalid filetype " << std::endl;
    }
}
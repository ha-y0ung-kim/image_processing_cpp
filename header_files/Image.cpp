#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

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
    else if (filetype == FileType::JPEG)
    {
        stbi_write_jpg("output.jpeg", width, height, num_channels, final_img, width * num_channels);
    }
    else
    {
        std::cout << "invalid filetype " << std::endl;
    }
}

void Image::convolution(Filter &filter, bool addpix)
{
    int num_channel = _vec.size();
    int height = _vec[0].size();
    int width = _vec[0][0].size();
    int pad_size = filter.get_kernel().size() - 1;
    int kernel_half = filter.get_kernel().size() / 2;

    vector3d output_image(num_channel, vector2d(height, std::vector<uint8_t>(width)));
    output_image = _vec;
    vector3d padded_image(num_channel, vector2d(height + pad_size, std::vector<uint8_t>(width + pad_size, 0)));

    for (int k = 0; k < num_channel; k++)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                padded_image[k][i + kernel_half][j + kernel_half] = _vec[k][i][j];
            }
        }
    }

    int kernel_width = filter.get_kernel().size();
    int kernel_height = filter.get_kernel()[0].size();

    double val;
    int ii, jj;

    for (int m = 0; m < num_channel; m++)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                val = 0.0;
                for (int k = 0; k < kernel_height; k++)
                {
                    for (int l = 0; l < kernel_width; l++)
                    {
                        ii = i - kernel_height / 2 + k;
                        jj = j - kernel_width / 2 + l;
                        val += (double)padded_image[m][ii + kernel_half][jj + kernel_half] * filter.get_kernel()[k][l];
                    }
                }
                if (addpix == false)
                {
                    output_image[m][i][j] = val;
                }
                else
                {
                    val += 128;
                    if (val < 0)
                    {
                        output_image[m][i][j] = 0;
                    }
                    else if (val > 255)
                    {
                        output_image[m][i][j] = 255;
                    }
                    else
                    {
                        output_image[m][i][j] = val;
                    }
                }
            }
        }
    }
    _vec = output_image;
}
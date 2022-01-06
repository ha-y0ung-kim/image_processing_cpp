#include <iostream>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include "vectortypes.h"

vector3d load_image(std::string filename)
{
    /*
    load an image into a 3d vector
    ask for an input image file name with type .PNG
    output
        image: 3d vector of the image
            the First dimension contains the R, G, B values of each pixel
            the second, and third dimension contains the pixel value of each row and the height
    */
    // std::string filename;
    // std::cout << "type input file name : ";
    // std::cin >> filename;
    const char *img_filename = filename.c_str();
    int width, height, num_channels;

    uint8_t *img = stbi_load(img_filename, &width, &height, &num_channels, 3);
    // while (img == NULL)
    // {
    //     std::cout << "Error in loading the image" << std::endl;
    //     std::cout << "type input file name : " << std::endl;
    //     std::cin >> filename;
    //     const char *img_filename = filename.c_str();
    //     img = stbi_load(img_filename, &width, &height, &num_channels, 0);
    // }

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
    stbi_image_free(img);
    return image;
}

void export_image(const vector3d &image)
{
    /*
    export an image into a .PNG file
    input
        image : image to be exported
    */
    int num_channels = image.size();
    int height = image[0].size();
    int width = image[0][0].size();

    uint8_t out[width * height * num_channels] = {0};

    int a = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < num_channels; k++)
            {
                out[a] = image[k][i][j];
                a += 1;
            }
        }
    }

    uint8_t *final_img;
    final_img = out;

    stbi_write_png("output.png", width, height, num_channels, final_img, width * num_channels);
}

void export_image_in_jpeg(const vector3d &image)
{
    /*
    export an image into a .PNG file
    input
        image : image to be exported
    */
    int num_channels = image.size();
    int height = image[0].size();
    int width = image[0][0].size();

    uint8_t out[width * height * num_channels] = {0};

    int a = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < num_channels; k++)
            {
                out[a] = image[k][i][j];
                a += 1;
            }
        }
    }

    uint8_t *final_img;
    final_img = out;
    // stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
    stbi_write_jpg("output.jpeg", width, height, num_channels, final_img, width * num_channels);
}

vector3d img_to_greyscale(const vector3d &image)
{
    /*
    Change an image into greyscale
    */
    int num_channels = image.size();
    int height = image[0].size();
    int width = image[0][0].size();

    vector3d grey_image(1, vector2d(height, std::vector<uint8_t>(width)));

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

// vector3d open_image_as_greyscale()
// {
//     /*
//     opens an image in greyscale
//     */
//     vector3d image, grey_image;
//     image = load_image();
//     grey_image = img_to_greyscale(image);
//     return grey_image;
// }
#include <vector>

#include "vectortypes.h"

vector3d convolution(const vector3d &image, const vector2dd &kernel, bool addpix)
{
    /*
    returns the convolution of an image.
    The image is zero-padded in the spatial domain to convolve through all the image pixels.

    Input
        image: image to be convolved
        kernel : convolution kernel
        addpix : set "true" if convolution kernel has a negative value
    Return
        output_image : convolved 3d image vector
    */

    int height = image[0].size();
    int width = image[0][0].size();
    int pad_size = kernel.size() - 1;
    int kernel_half = kernel.size() / 2;

    vector3d output_image(1, vector2d(height, std::vector<uint8_t>(width)));
    output_image = image;
    vector3d padded_image(1, vector2d(height + pad_size, std::vector<uint8_t>(width + pad_size, 0)));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            padded_image[0][i + kernel_half][j + kernel_half] = image[0][i][j];
        }
    }

    int kernel_width = kernel.size();
    int kernel_height = kernel[0].size();

    double val;
    int ii, jj;

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
                    val += (double)padded_image[0][ii + kernel_half][jj + kernel_half] * kernel[k][l];
                }
            }
            if (addpix == false)
            {
                output_image[0][i][j] = val;
            }
            else
            {
                val += 128;
                if (val < 0)
                {
                    output_image[0][i][j] = 0;
                }
                else if (val > 255)
                {
                    output_image[0][i][j] = 255;
                }
                else
                {
                    output_image[0][i][j] = val;
                }
            }
        }
    }
    return output_image;
}
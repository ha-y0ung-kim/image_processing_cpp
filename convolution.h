#include <vector>

std::vector<std::vector<std::vector<uint8_t>>> convolution(std::vector<std::vector<std::vector<uint8_t>>> image, std::vector<std::vector<double>> kernel, bool addpix)
{
    int height = image[0].size();
    int width = image[0][0].size();

    std::vector<std::vector<std::vector<uint8_t>>> output_image(1, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(width)));
    output_image = image;

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

                    ii = (i - kernel_height / 2 + k + height) % height;
                    jj = (j - kernel_width / 2 + l + width) % width;

                    val += (double)image[0][ii][jj] * kernel[k][l];

                    // ii = i - kernel_height / 2 + k;
                    // jj = j - kernel_width / 2 + l;
                    // if (ii >= 0 & ii < width & jj >= 0 & jj < height)
                    // {
                    //     val += (double)image[0][ii][jj] * kernel[k][l];
                    // }
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
#include <vector>
#include <iostream>

std::vector<std::vector<std::vector<uint8_t>>> operator+(const std::vector<std::vector<std::vector<uint8_t>>> &vec_a,
                                                         const std::vector<std::vector<std::vector<uint8_t>>> &vec_b)
{
    /*
     * Overload operator+ to allow addition of two double vectors
     * of the same size. The return value is another vector formed by
     * adding the corresponding elements of vec_a and vec_b.
     */

    assert(vec_a.size() == vec_b.size());
    int width = vec_a.size();
    int height = vec_a[0].size();
    int channel = vec_a[0][0].size();

    std::vector<std::vector<std::vector<uint8_t>>> vec_sum(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(channel)));

    for (auto i = 0; i < width; i++)
    {
        for (auto j = 0; j < height; j++)
        {
            for (auto k = 0; k < channel; k++)
            {
                vec_sum[i][j][k] = vec_a[i][j][k] + vec_b[i][j][k];
            }
        }
    }
    return vec_sum;
}

std::vector<std::vector<std::vector<uint8_t>>> operator*(const double &number,
                                                         const std::vector<std::vector<std::vector<uint8_t>>> &vec_a)
{
    int width = vec_a.size();
    int height = vec_a[0].size();
    int channel = vec_a[0][0].size();

    std::vector<std::vector<std::vector<uint8_t>>> vec_mul(width, std::vector<std::vector<uint8_t>>(height, std::vector<uint8_t>(channel)));

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < channel; k++)
            {
                vec_mul[i][j][k] = number * vec_a[i][j][k];
            }
        }
    }
    return vec_mul;
}

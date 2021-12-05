#include <vector>
#include <iostream>

#include "vectortypes.h"

vector3d operator+(const vector3d &vec_a, const vector3d &vec_b)
{
    /*
    Overload operator+ to allow element wise addition of two 3d dimensional vectors of the same size
    */

    assert(vec_a.size() == vec_b.size());
    assert(vec_a[0].size() == vec_b[0].size());
    assert(vec_a[0][0].size() == vec_b[0][0].size());

    int channel = vec_a.size();
    int height = vec_a[0].size();
    int width = vec_a[0][0].size();

    vector3d vec_sum(channel, vector2d(height, std::vector<uint8_t>(width)));

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < channel; k++)
            {
                vec_sum[k][j][i] = vec_a[k][j][i] + vec_b[k][j][i];
            }
        }
    }
    return vec_sum;
}

vector3d operator*(const double &number, const vector3d &vec_a)
{
    /*
    Overload operator* to allow multiplication of a double with a 3d vector
    */
    int channel = vec_a.size();
    int height = vec_a[0].size();
    int width = vec_a[0][0].size();

    vector3d vec_mul(channel, vector2d(height, std::vector<uint8_t>(width)));

    for (int i = 0; i < channel; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < width; k++)
            {
                vec_mul[i][j][k] = number * vec_a[i][j][k];
            }
        }
    }
    return vec_mul;
}

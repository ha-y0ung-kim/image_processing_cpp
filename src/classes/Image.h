/**
 * @file Image.h
 * @author Ha Young Kim
 * @brief Image class
 * @version 0.1
 * @date 2022-01-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "../vectortypes.h"
#include "Filter.h"

/**
 *
 * @brief enum class FileType that with image file extensions PNG, JPEG
 */
enum class FileType
{
    PNG,
    JPEG
};

/**
 * @brief Image class
 */
class Image
{
private:
    FileType _filetype;
    const std::string _path; /** string that contains a file path */
    vector3d _vec;           /** 3 dimensional double vector with image values */

public:
    /**
     * @brief Construct a new Image object
     * @param string with image file location
     */
    Image(const std::string &);

    /**
     * @brief function that converts color image to grey image
     */
    void img_to_greyscale();

    /**
     * @brief exports image according to image extension type
     * @param FileType output image extension type. Set by the user
     * Output is saved on either "output.png" or "output.jpeg"
     */

    void export_image(const FileType &);

    /**
     * @brief convolves a image with a filter kernel
     * The image is zero-padded in the spatial domain to convolve through all the image pixels
     * @param Filter filter kernel that should be convolved throughout the image
     * @param bool set "true" if the convolution kernel has a negative value. else, set "false"
     */
    void convolution(const Filter &);
    // https://stackoverflow.com/questions/4282014/c-abstract-class-cant-have-a-method-with-a-parameter-of-that-class
};

#endif // IMAGE_H
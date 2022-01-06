#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "vectortypes.h"
#include "Filter.h"

enum class FileType
{
    PNG,
    JPEG
};

enum class ImageColor
{
    color,
    gray
};

class Image
{
private:
    FileType _filetype;
    std::string _path;
    vector3d _vec;
    ImageColor _imgcolor;

public:
    Image(std::string);
    Image(vector3d);

    void img_to_greyscale();

    void export_image(FileType);

    void convolution(Filter &, bool);
    // https://stackoverflow.com/questions/4282014/c-abstract-class-cant-have-a-method-with-a-parameter-of-that-class
};

#endif // IMAGE_H
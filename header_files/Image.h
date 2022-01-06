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

class Image
{
private:
    FileType _filetype;
    std::string _path;
    vector3d _vec;

public:
    Image(std::string);

    void img_to_greyscale();

    void export_image(FileType);

    void convolution(Filter &, bool);
    // https://stackoverflow.com/questions/4282014/c-abstract-class-cant-have-a-method-with-a-parameter-of-that-class
};

#endif // IMAGE_H
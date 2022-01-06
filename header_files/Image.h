#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "vectortypes.h"

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
    Image(vector3d);

    void img_to_greyscale();
    
    void export_image(FileType);
};

#endif // IMAGE_H
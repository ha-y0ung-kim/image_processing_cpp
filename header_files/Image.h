#ifndef IMAGE_H
#define IMAGE_H

#include <string>

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
    

public:
    Image(std::string);

    void load_image();
    void export_image();
    void export_image_in_jpeg();
    void img_to_greyscale();
    void open_image_as_greyscale();
};

#endif // IMAGE_H
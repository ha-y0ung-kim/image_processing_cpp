#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include "vectortypes.h"

enum class FilterType
{
    Blur,
    EdgeDetect
};

class Imagefilter
{
private:
    FilterType _filtertype;

public:

};

#endif // IMAGEFILTER_H
#ifndef FILTER_H
#define FILTER_H

#include "vectortypes.h"

enum class FilterType
{
    MeanBlur,
    GaussianBlur,
    Laplacian,
    Sobal_x,
    Sobal_y,
    Unsharp
};

class Filter
{
private:
    FilterType _filtertype;

public:
    void get_kernel_size();
    virtual void filtering();

};

#endif // FILTER_H
#ifndef FILTER_H
#define FILTER_H

#include "vectortypes.h"

class Filter
{
protected:
    vector2dd _kernel;
    int _kernel_size;

public:
    virtual void setfilter() = 0;
    vector2dd get_kernel();

    virtual ~Filter() = default;
};

#endif // FILTER_H
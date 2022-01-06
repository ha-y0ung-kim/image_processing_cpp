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
};

#endif // FILTER_H
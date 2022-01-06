#ifndef FILTER_H
#define FILTER_H

#include "vectortypes.h"

class Filter
{
protected:
    vector2dd _kernel;
    int _kernel_size;

public:
    virtual void setfilter();
    vector2dd get_kernel();
};

#endif // FILTER_H
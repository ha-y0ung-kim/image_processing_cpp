#include <iostream>
#include "Filter.h"

vector2dd Filter::get_kernel() const
{
    return kernel;
}

bool Filter::get_negval() const
{
    return neg_value;
}

#include <iostream>
#include "Filter.h"

vector2dd Filter::get_kernel()
{
    return kernel;
}

bool Filter::get_negval()
{
    return neg_value;
}
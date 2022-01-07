/**
 * @file Filter.h
 * @author Ha Young Kim
 * @brief Filter class
 * @version 0.1
 * @date 2022-01-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef FILTER_H
#define FILTER_H

#include "../vectortypes.h"

class Filter
{
protected:
    vector2dd kernel; /** 2dimensional double vector with kernel value*/
    int kernel_size;  /** integer with kernel size */

public:
    /**
     * @brief pure virtual function of setting filters
     */
    virtual void setfilter() = 0;
    /**
     * @brief Get the kernel object
     *
     * @return vector2dd
     */
    vector2dd get_kernel();

    /**
     * @brief Destroy the Filter object
     *
     */

    virtual ~Filter() = default;
};

#endif // FILTER_H
/**
 * @file filterset.h
 * @author Ha Young Kim
 * @brief various Filter child classes
 * @version 0.1
 * @date 2022-01-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef FILTERSET_H
#define FILTERSET_H

#include "Filter.h"

/**
 * @brief MeanBlur class
 * setting kernel of mean filter
 * The resulting image is Blurred
 */
class MeanBlur : public Filter
{
private:
public:
    /**
     * @brief Construct a new Mean Blur object
     * @param integer of kernel_size
     */
    MeanBlur(const int);

    /**
     * @brief set mean filter kernel
     * set a mean kernel of size (kernel_size * kernel_size)
     */
    void set_filter() override;
};

/**
 * @brief Gaussain filter class
 * set a gaussian filter kernel
 * Image gets blurred
 */
class GaussianBlur : public Filter
{
private:
    double _variance; /** variance of the gaussian */

public:
    /**
     * @brief Construct a new Gaussian Blur object
     * @param integer of kernel_size
     * @param double variance of the gaussian function applied
     */
    GaussianBlur(const int, const double);

    /**
     * @brief set gaussian filter kernel
     * set a gaussian kernel of size (kernel_size * kernel_size) and gaussian variance of _variance
     */
    void set_filter() override;
};

/**
 * @brief Laplacian filter class
 * set a laplacian filter kernel
 * Edge of the image is detected
 */
class Laplacian : public Filter
{
private:
public:
    /**
     * @brief Construct a new Laplacian filter object
     * @param integer of kernel_size
     */
    Laplacian(const int);

    /**
     * @brief set laplacian filter kernel
     * set  a laplacian kernel of size (kernel_size * kernel_size)
     */
    void set_filter() override;
};

/**
 * @brief Sobal filter in x direction (horizontal) class
 * set a sobal filter kernel in x direction
 * the horizontal edge of an image is detected
 */
class Sobal_x : public Filter
{
private:
public:
    /**
     * @brief Construct a new Sobal_x object
     * @param integer of kernel_size. fixed as 3
     */
    Sobal_x(const int);

    /**
     * @brief set sobal kernel in x direction
     * set a sobal filter kernel of size (3 x 3) that detects edge in x direction
     *
     */
    void set_filter() override;
};

/**
 * @brief Sobal filter in y direction (vertical) class
 * set a sobal filter kernel in y direction
 * the vertical edge of an image is detected
 */
class Sobal_y : public Filter
{
private:
public:
    /**
     * @brief Construct a new Sobal_y object
     * @param integer of kernel_size. fixed as 3
     */
    Sobal_y(const int);

    /**
     * @brief set sobal kernel in y direction
     * set a sobal filter kernel of size (3 x 3) that detects edge in y direction
     *
     */
    void set_filter() override;
};

/**
 * @brief  Roberts Cross Edge Detector in x direction (horizontal) class
 * set a roberts cross edge detector kernel in x direction
 * the horizontal edge of an image is detected
 */
class Robert_Cross_x : public Filter
{
private:
public:
    /**
     * @brief Construct a new Rober_Cross object
     * @param  integer of kernel_size.
     */
    Robert_Cross_x(const int);

    /**
     * @brief set Robert_Cross kernel in x direction
     * set a robert cross edge detection kernel of size (2x2) that detects edge in x direction
     *
     */
    void set_filter() override;
};

/**
 * @brief  Roberts Cross Edge Detector in y direction (vertical) class
 * set a roberts cross edge detector kernel in y direction
 * the vertical edge of an image is detected
 */
class Robert_Cross_y : public Filter
{
private:
public:
    /**
     * @brief Construct a new Rober_Cross object
     * @param  integer of kernel_size.
     */
    Robert_Cross_y(const int);

    /**
     * @brief set Robert_Cross kernel in y direction
     * set a robert cross edge detection kernel of size (2x2) that detects edge in y direction
     */
    void set_filter() override;
};

#endif // FILTERSET_H
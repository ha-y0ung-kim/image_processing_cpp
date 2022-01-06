
#ifndef FILTERSET_H
#define FILTERSET_H

#include "filter.h"

class MeanBlur : public Filter
{
private:
public:
    MeanBlur(int);
    void setfilter() override;
};

class GaussianBlur : public Filter
{
private:
    double _variance;

public:
    GaussianBlur(int, double);
    void setfilter() override;
};

class Laplacian : public Filter
{
private:
public:
    Laplacian(int);
    void setfilter() override;
};

class Sobal_x : public Filter
{
private:
public:
    Sobal_x();
    void setfilter() override;
};

class Sobal_y : public Filter
{
private:
public:
    Sobal_y();
    void setfilter() override;
};

#endif // FILTERSET_H
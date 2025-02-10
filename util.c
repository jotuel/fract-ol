#include "fractol.h"

int case_0(double v, double t, double p)
{
    return get_rgba(fmin(fmax(255 * v + 0.5, 0), 255),
    fmin(fmax(255 * t + 0.5, 0), 255),
    fmin(fmax(255 * p + 0.5, 0), 255), 0xFF);
}

int case_1(double q, double v, double p)
{
    return get_rgba(fmin(fmax(255 * q + 0.5, 0), 255),
    fmin(fmax(255 * v + 0.5, 0), 255),
    fmin(fmax(255 * p + 0.5, 0), 255), 0xFF);
}

int case_2(double p, double v, double t)
{
    return get_rgba(fmin(fmax(255 * p + 0.5, 0), 255),
    fmin(fmax(255 * v + 0.5, 0), 255),
    fmin(fmax(255 * t + 0.5, 0), 255), 0xFF);
}

int case_3(double p, double q, double v)
{
    return get_rgba(fmin(fmax(255 * p + 0.5, 0), 255),
    fmin(fmax(255 * q + 0.5, 0), 255),
    fmin(fmax(255 * v + 0.5, 0), 255), 0xFF);
}

int case_4(double t, double p, double v)
{
    return get_rgba(fmin(fmax(255 * t + 0.5, 0), 255),
    fmin(fmax(255 * p + 0.5, 0), 255),
    fmin(fmax(255 * v + 0.5, 0), 255), 0xFF);
}

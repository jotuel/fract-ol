
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:02:32 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/05 19:46:07 by jtuomi           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static inline double cnorm(double complex z)
{
    return (creal(z) * creal(z) + cimag(z) * cimag(z));
}

static void calculate_values(double x, double complex c,
                             double complex z, double y)
{
    double dwell;
    double g;
    int i;

    i = 0;
    while(i < ITERATIONS)
    {
        z = z * z + c;
        if (cnorm(z) > RADIUS)
            break;
    }
    g = 1.;
    if (i < ITERATIONS)
    {
        dwell = i + 1 - log2(log(cabs(z)));
        g = 0.5 - 0.5 * cos(M_PI * dwell);
    }
    return (255 * g + 255);
}

static void mandelbrot_set(void *param, int j, int h, int i)
{
    mandelbrot_t *mb;
    double y;
    double x;
    double complex c;
    double complex z;

    mb = param;
    while(WIDTH > j)
    {
        y = (REN_HEI - (j + 0.5) / REN_HEI * RADIUS);
        while(HEIGHT > h)
        {
            x = (y + 0.5 - REN_WID / 2) / REN_WID * RADIUS;
            c = x + I * y;
            z = 0;
            mlx_put_pixel(mb->image, j, h, calculate_values(x, c, z, y));
            h++;
        }
        h = 0;
        j++;
    }
}

void mandelbrot_initialize(void *param)
{
    mandelbrot_t mandelbrot;
    mlx_image_t *image;

    image = param;
    mandelbrot.image = image;
    mandelbrot.c = CMPLX(0.0 + 0.0 * I, 1. + -2.0 * I);
    mandelbrot.iter = ITERATIONS;
    mandelbrot.radius = RADIUS * RADIUS;
    mandelbrot.color = 0x000000FF;
    mandelbrot_set(&mandelbrot, 0, 0, 0);
}

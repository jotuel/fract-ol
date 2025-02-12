
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:02:32 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/12 11:48:56 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <omp.h>

static inline int case_default(double val, double p, double q)
{
    return (get_rgba(fmin(fmax(255 * val + 0.5, 0), 255),
             fmin(fmax(255 * p + 0.5, 0), 255),
             fmin(fmax(255 * q + 0.5, 0), 255),
             0xFF));
}

static int hsv2rgba(double hue, double sat, double val)
{
    double f;
    double p;
    double q;
    double t;
    double i;

    hue = 6 * (hue - floor(hue));
    i = floor(hue);
    f = hue - i;
    p = val * (1 - sat);
    q = val * (1 - (sat * f));
    t = val * (1 - (sat * (1 - f)));
    if ((int)i == 0)
        return case_0(val, t, p);
    else if ((int)i == 1)
        return case_1(q, val, p);
    else if ((int)i == 2)
        return case_2(p, val, t);
    else if ((int)i == 3)
        return case_3(p, q, val);
    else if ((int)i == 4)
        return case_4(t, p, val);
    else
        return case_default(val, p, q);
}

static int calculate_values(t_mandelbrot *mb,
                            double complex c,
                            double complex z,
                            double complex dc)
{
    int i;

    i = 0;
    while(++i < mb->iter)
    {
        dc = 2 * z * dc + 1;
        z = z * z + c;
        if (cnorm(z) > mb->radius)
            break;
    }
    if (i < mb->iter)
    {
        mb->de = 2 * z * log(cabs(z)) / dc;
        mb->hue = fmod(1 + carg(mb->de) / (2 * M_PI), 1);
        mb->sat = 0.25;
        mb->val = tanh(cabs(mb->de) / mb->px / mb->aa);
        return hsv2rgba(mb->hue, mb->sat, mb->val);
    }
    else
        return (-1);
}

static void mandelbrot_set(t_mandelbrot *mb, int w, int h)
{
    double y;
    double x;


    while(mb->w > w)
    {
        y = (mb->h / 2. - (w + mb->x + 0.5)) / (mb->h / 2.) * RADIUS;
        while(mb->h > h)
        {
            x = (h + mb->y + 0.5 - mb->w / 2.) / (mb->h / 2.) * RADIUS;
            mb->c = x * mb->zoom + I * (y * mb->zoom);
            mlx_put_pixel(mb->image, w, h, calculate_values(mb, mb->c, 0, 0));
            h++;
        }
        h = 0;
        w++;
    }
}

void mandelbrot_initialize(void *param)
{
    t_mandelbrot* mandelbrot;

    mandelbrot = param;
    mandelbrot->aa = 1;
    mandelbrot->w = mandelbrot->image->width;
    mandelbrot->h = mandelbrot->image->height;
    mandelbrot->px = RADIUS / mandelbrot->w / 2;
    mandelbrot->radius = RADIX;
    mandelbrot->iter = ITERATIONS;
    mandelbrot->as_rat = (double)mandelbrot->image->width / (double)mandelbrot->image->height;
    printf("x:%f y:%f", mandelbrot->x, mandelbrot->y);
    mandelbrot_set(mandelbrot, 0, 0);
}

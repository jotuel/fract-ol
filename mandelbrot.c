
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:02:32 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/10 15:28:30 by marvin           \__/    i               */
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
        if (cnorm(z) > RADIX)
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

static void mandelbrot_set(t_mandelbrot *mb, int j, int h)
{
    double y;
    double x;


    while(mb->w > j)
    {
        #pragma omp parallel num_threads(12)
        y = (mb->h / 2 - (j + 0.5)) / (mb->h / 2) * RADIUS;
        while(mb->h > h)
        {
            x = (h + 0.5 - mb->w / 2) / (mb->h / 2) * RADIUS;
            mb->c = x + I * y;
             mlx_put_pixel(mb->image, j, h, calculate_values(mb, mb->c, 0, 0));
            h++;
        }
        h = 0;
        j++;
    }
}

void mandelbrot_initialize(void *param)
{
    static t_mandelbrot mandelbrot;
    mlx_image_t* image;

    image = param;
    mandelbrot.aa = 4;
    mandelbrot.w = WIDTH * mandelbrot.aa;
    mandelbrot.h = HEIGHT * mandelbrot.aa;
    mandelbrot.px = RADIUS / mandelbrot.w / 2;
    mandelbrot.image = image;
    mandelbrot.zoom = 1.;
    mandelbrot.iter = ITERATIONS;
    mandelbrot.radius = RADIUS * RADIUS;
    mandelbrot.as_rat = (double)WIDTH / (double)HEIGHT;
    mandelbrot_set(&mandelbrot, 0, 0);
}

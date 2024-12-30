/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:02:32 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/24 13:39:20 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static void calculate_values(mandelbrot_t *mb, int i, int x, int y)
{
    mb->z = CMPLX(x / (REN_WID * 0.5), y / (REN_HEI * 0.5));
    while(pow(creal(mb->z), 2) + pow(cimag(mb->z), 2) < fabs(mb->radius) && 
    i < mb->iter)
    {
        mb->tmp = pow(creal(mb->z), 2) - pow(cimag(mb->z), 2);
        mb->tmp = 2 * creal(mb->z) * cimag(mb->z) * I;
        mb->z = creal(mb->tmp) + creal(mb->c);
        mb->z = cimag(mb->tmp) + cimag(mb->c);
        i++;
    }
    if (i == mb->iter)
        mlx_put_pixel(mb->image, x, y, mb->color);
    else
        mlx_put_pixel(mb->image, x, y, get_rgba(i, i, i, 0xFF));
}

static void mandelbrot_set(void *param, int x, int y, int i)
{
    mandelbrot_t *mb;

    mb = param;
    while(REN_WID > x)
    {
        while(REN_HEI > y)
        {
            calculate_values(mb, i, x, y);
            y++;
        }
        y = 0;
        x++;
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

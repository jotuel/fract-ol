/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:02:32 by jtuomi            #+#    #+#             */
/*   Updated: 2025/01/16 16:35:56 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static void calculate_pixels(mandelbrot_t *mb, int i)
{
    if (cabs(mb->z) > 4)
    {
        mlx_put_pixel(mb->image, creal(mb->c) * SCALE_H + SCALE_W,
                      cimag(mb->c) * SCALE_H+SCALE_W, 0xFFFFFFFF);
        return ;
    }
    if (i == ITERATIONS)
        mlx_put_pixel(mb->image, creal(mb->c) * SCALE_H + SCALE_W,
                      cimag(mb->c) * SCALE_H+SCALE_W, mb->color);
    mb->z = pow(mb->z, 2) + mb->c;
    calculate_pixels(mb, i + 1);
}

static void mandelbrot_set(void *param, int i, double x, double y)
{
    mandelbrot_t *mb;

    mb = param;
    while(x < 2.0)
    {
        while(y < 1)
        {
            mb->c = CMPLX(y, x * I);
            calculate_pixels(mb, i);
        }
        y = -1;
        x += 0.0015;
    }
}

void mandelbrot_initialize(void *param)
{
    mandelbrot_t mandelbrot;
    mlx_image_t *image;

    image = param;
    mandelbrot.image = image;
    mandelbrot.z = 0;
    mandelbrot.iter = ITERATIONS;
    mandelbrot.radius = RADIUS * RADIUS;
    mandelbrot.color = 0x000000FF;
    mandelbrot_set(&mandelbrot, 0, -2, -1);
}

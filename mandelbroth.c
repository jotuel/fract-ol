/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbroth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:02:32 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/22 14:49:01 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void mandelbroth_initialize(void *param)
{
    mandelbrot_t *mandelbrot;
    mlx_image_t *image;
    complex_t c;
    int iterations;
    int color;
    double complex radius;

    color = 0x000000FF;
    iterations = 100;
    radius = 0.0;
    c.x = 0.0 + 0.0 * I;
    c.y = 1. + -2.0 * I;
    image = param;
    mandelbrot.image = image;
    mandelbrot.c = c;
    mandelbrot.iter = iterations;
    mandelbrot.radius = radius;
    mandelbrot.color = color;
    mandelbroth_set(&mandelbrot);
}

static void calculate_values(mandelbrot_t *mb, int i, int x, int y)
{
    mb->z.x = x / WIDTH;
    mb->z.y = y / HEIGHT;
    while(fabs(mb->radius) < RADIUS && i < ITERATIONS)
    {
        mb->tmp.x = pow(mb->z.x, 2) - pow(mb->z.y, 2);
        mb->tmp.y = 2 * mb->z.x * mb->z.y;
        mb->z.x = mb->tmp.x + mb->c.x;
        mb->z.y = mb->tmp.y + mb->c.y;
        i++;
        mb->radius = pow(mb->z.x, 2) + pow(mb->z.y, 2);
    }
    if (i == ITERATIONS)
        mlx_put_pixel(mb->image, x, y, mb->color);
    else
        mlx_put_pixel(mb->image, x, y, mlx_rgba(i, i, i, 0xFF));
}

void mandelbroth_set(void *param)
{
    int x;
    int y;
    int i;
    mandelbrot_t *mb;
    complex_t z;

    x = 0;
    y = 0;
    i = 0;
    mb = param;
    while(WIDTH > x)
    {
        while(HEIGHT > y)
        {
            calculate_values(mb, i, x, y);
            y++;
        }
        y = 0;
        x++;
    }
}


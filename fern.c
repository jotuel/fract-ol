/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fern.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:39:04 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/22 22:26:50 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void calculus(fern_t *fern)
{
        if (fern->r < 0.01)
        {
            fern->xn = 0.0;
            fern->yn = 0.16 * fern->y;
        }
        else if (fern->r < 0.86)
        {
            fern->xn = 0.86 * fern->x + 0.04 * fern->y;
            fern->yn = -0.04 * fern->x + 0.85 * fern->y + 1.6;
        }
        else if (fern->r < 0.93)
        {
            fern->xn = 0.2 * fern->x - 0.26 * fern->y;
            fern->yn = 0.23 * fern->x + 0.22 * fern->y + 1.6;
        }
        else
        {
            fern->xn = -0.15 * fern->x + 0.28 * fern->y;
            fern->yn = 0.26 * fern->x + 0.24 * fern->y + 0.44;
        }
}

static void fern_fractal(fern_t fern)
{
    while (fern.iter++ < FITERATIONS)
    {
        fern.r = ((double)rand() / (double)RAND_MAX);
        calculus(&fern);
        mlx_put_pixel(fern.image, fern.xn * 100 + 300, fern.yn * 72, fern.color += fern.iter);
        fern.y = fern.yn;
        fern.x = fern.xn;
    }
}

void fern_initialize(void *param)
{
    fern_t fern;

    fern.iter = 0;
    fern.x = 0.0;
    fern.y = 0.0;
    fern.xn = 0.0;
    fern.yn = 0.0;
    fern.c = 0.0;
    fern.image = param;
    fern.color = 0xFFFFFFFF;
    fern_fractal(fern);
}

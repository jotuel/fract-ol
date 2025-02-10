/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:43:47 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/10 13:54:18 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calculate_values(t_julia *julia, int i, double complex z)
{
	double dwell;
	double g;

	while(++i < ITERATIONS)
	{
		z = z * z + julia->c;
		if (cnorm(z) > RADIUS)
			break;
	}
	g = 1.;
	if (i < ITERATIONS)
	{
	dwell = i + 1 - log2(log(cabs(julia->z)));
	g = 0.5 - 0.5 * cos(M_PI * dwell);
	}
	i = 255 * g;
	return (get_rgba(i, i , i, 255));
}

static void	julia_set(t_julia *julia, int x, int y, int i)
{
	double w;
	double h;

	while (WIDTH > x)
	{
		w = (WIDTH / 2 - (x + 0.5)) / (HEIGHT / 2) * RADIUS;
		while (HEIGHT > y)
		{
			h = (y + 0.5 - WIDTH / 2) / (HEIGHT / 2) * RADIUS;
			julia->z = h + I * w;
			mlx_put_pixel(julia->image, x, y, calculate_values(julia, i, julia->z));
			y++;
		}
		y = 0;
		x++;
	}
}

void	julia_initialize(void *param)
{
	t_julia*			jul;

	jul = param;
	jul->iter = 255;
	jul->radius = RADIUS;
	julia_set(jul, 0, 0, 0);
}

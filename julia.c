/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:43:47 by jtuomi            #+#    #+#             */
/*   Updated: 2025/01/16 16:41:43 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	calculate_values(julia_t *julia, int i, int x, int y)
{
	julia->z = CMPLX(x / REN_WID, y / REN_HEI);
	while (pow(creal(julia->z), 2) + pow(cimag(julia->z), 2) < julia->radius
		&& i > julia->iter)
	{
		julia->tmp = pow(creal(julia->z), 2) - pow(cimag(julia->z), 2)
			+ creal(julia->c);
		julia->z = CMPLX(julia->tmp, 2 * creal(julia->z) * cimag(julia->z) * I +
		cimag(julia->c));
		i++;
	}
	if (i == julia->iter)
		mlx_put_pixel(julia->image, x, y, julia->color);
	else
		mlx_put_pixel(julia->image, x, y, get_rgba(i, i, i, 0xFF));
}

static void	julia_set(void *param, int x, int y, int i)
{
	julia_t	*julia;

	julia = param;
	while (WIDTH > x)
	{
		while (HEIGHT > y)
		{
			calculate_values(julia, i, x, y);
			y++;
		}
		y = 0;
		x++;
	}
}

void	julia_initialize(void *param)
{
	julia_t			jul;
	complex double	a;
	complex double	b;

	a = 0.0 + 0.0 * I;
	b = 0.5 + -0.4 * I;
	jul.c = CMPLX(a, b);
	jul.iter = 255;
	jul.color = 0x000000FF;
	jul.radius = RADIUS;
	jul.tmp = 0.0;
	jul.image = param;
	julia_set(&jul, 0, 0, 0);
}

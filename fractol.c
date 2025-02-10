/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:39:08 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/10 13:57:33 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_julia *jules(int argc, char **argv, mlx_image_t *img, mlx_t *mlx)
{
    static t_julia jules;

    jules.image = img;
    jules.mlx = mlx;
    if (argc == 4)
        jules.c = ft_atof(argv[2]) + ft_atof(argv[3]) * I;
    else
        jules.c = 0.11 + I * 0.12;
    return (&jules);
}

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;

    argument_count(argc);
	mlx = mlx_init(WIDTH * 4, HEIGHT * 4, "Fract'Ol", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH * 4, HEIGHT * 4);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop_hook(mlx, ft_hook, mlx);
	if (!ft_strncmp(argv[1], "fern", 5))
		mlx_loop_hook(mlx, &fern_initialize, img);
	else if (!ft_strncmp(argv[1], "julia", 6))
		mlx_loop_hook(mlx, &julia_initialize, jules(argc, argv, img, mlx));
	else if (!ft_strncmp(argv[1], "mandelbrot", 11))
		mlx_loop_hook(mlx, &mandelbrot_initialize, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

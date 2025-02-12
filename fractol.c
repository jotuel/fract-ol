/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:39:08 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/12 03:20:50 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "MLX42/include/MLX42/MLX42.h"

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

static t_mandelbrot *mandelbrot(mlx_image_t *img, mlx_t *mlx)
{
    static t_mandelbrot mandelbrot;

    mandelbrot.image = img;
    mandelbrot.mlx = mlx;
    mandelbrot.zoom = 1.;
    mandelbrot.x = 0;
    mandelbrot.y = 0;
    mlx_scroll_hook(mlx, &my_scrollhook, &mandelbrot);
    mlx_key_hook(mlx, &my_keyhook, &mandelbrot);
    return &mandelbrot;
}

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;

    argument_count(argc);
	mlx = mlx_init(WIDTH, HEIGHT, "Fract'Ol", true);
	if (!mlx)
		ft_error();
    mlx_set_setting(MLX_STRETCH_IMAGE, true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	if (!ft_strncmp(argv[1], "fern", 5))
		mlx_loop_hook(mlx, &fern_initialize, img);
	else if (!ft_strncmp(argv[1], "julia", 6))
		mlx_loop_hook(mlx, &julia_initialize, jules(argc, argv, img, mlx));
	else if (!ft_strncmp(argv[1], "mandelbrot", 11))
		mlx_loop_hook(mlx, &mandelbrot_initialize, mandelbrot(img, mlx));
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

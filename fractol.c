/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:39:08 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/02 15:08:19 by jtuomi           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "MLX42/include/MLX42/MLX42.h"

static void	ft_error(void)
{
	ft_putendl_fd((char *)mlx_strerror(errno), 2);
	exit(EXIT_FAILURE);
}

static void	ft_hook(void *param)
{
	mlx_t	*mlx = param;

	ft_printf("WIDTH: %d | HEIGHT %d\n", mlx->width, mlx->height);
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
}



void my_keyhook(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx = param;

    if (keydata.key == MLX_KEY_ESC && keydata.action == MLX_PRESS)
        mlx_terminate(mlx);
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        puts("Key up");
}


static void argument_coount(int argc)
{
    if (argc != 2)
    {
        ft_printf("Usage: ./fractol [fern | julia | mandelbrot]\n");
        ft_error();
    }
}

static void close_window_hook(void *param)
{
    mlx_t *t;

    t = param;
    mlx_close_window(t);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
    mlx_t		*mlx;
    int x;
    int y;

    x = 0;
    y = 0;
	mlx = param;
	if (ydelta > 0)
    {
        mlx_get_mouse_pos(mlx, &x, &y);
        // TODO: Implement zooming.
    }
	else if (ydelta < 0)
    {
        mlx_get_mouse_pos(mlx, &x, &y);
    }
	(void)xdelta;
}

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;

    argument_count(argc);
	mlx = mlx_init(WIDTH, HEIGHT, "Fract'Ol", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, REN_HEI, REN_HEI);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop_hook(mlx, ft_hook, mlx);
	if (!ft_strncmp(argv[1], "fern", 5))
		mlx_loop_hook(mlx, &fern_initialize, img);
	else if (!ft_strncmp(argv[1], "julia", 6))
		mlx_loop_hook(mlx, &julia_initialize, img);
	else if (!ft_strncmp(argv[1], "mandelbrot", 11))
		mlx_loop_hook(mlx, &mandelbrot_initialize, img);
	mlx_scroll_hook(mlx, &my_scrollhook, img);
    mlx_close_hook(mlx, &close_window_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

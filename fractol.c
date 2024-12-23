/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:39:08 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/23 15:54:54 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(errno));
	exit(EXIT_FAILURE);
}

static void	ft_hook(void *param)
{
	const mlx_t	*mlx = param;

	ft_printf("WIDTH: %d | HEIGHT %d\n", mlx->width, mlx->height);
}

static void argument_count(int argc)
{
    if (argc != 2)
    {
        ft_printf("Usage: ./fractol [fern | julia | mandelbrot]\n");
        ft_error();
    }
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
    mlx_t		*mlx;
    int x;
    int y;

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
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, "Fract'Ol", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	ft_memset(img->pixels, 0xFF00FFF0, img->width * img->height
		* sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
	if (!ft_strncmp(argv[1], "fern", 5))
		mlx_loop_hook(mlx, &fern_initialize, img);
	else if (!ft_strncmp(argv[1], "julia", 6))
		mlx_loop_hook(mlx, &julia_initialize, img);
	else if (!ft_strncmp(argv[1], "mandelbrot", 11))
		mlx_loop_hook(mlx, &mandelbrot_initialize, img);
	mlx_scroll_hook(mlx, &my_scrollhook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

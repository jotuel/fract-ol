/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:39:08 by jtuomi            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/12/24 13:40:40 by jtuomi           ###   ########.fr       */
=======
/*   Updated: 2025/01/30 17:11:23 by marvin           \__/    i               */
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
static void argument_count(int argc)
=======
void my_keyhook(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx = param;

    if (keydata.key == MLX_KEY_ESC && keydata.action == MLX_PRESS)
        mlx_terminate(mlx);
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        puts("Key up");
}

void my_scrollhook(double xdelta, double ydelta, void* param)
>>>>>>> Stashed changes
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
	mlx = mlx_init(WIDTH, HEIGHT, "Fract'Ol", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, REN_WID, REN_HEI);
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
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

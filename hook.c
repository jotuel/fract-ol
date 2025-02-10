/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   hook.c                                         __/  \__  i (_(_)(_|(/_   */
/*                                                 /  \__/  \ v  _ _|_        */
/*   By: marvin <marvin@42.fr>                     \__/  \__/ e _>(_| | --    */
/*                                                 /  \__/  \ .  _  _ |       */
/*   Created: 2025/02/08 23:22:09 by marvin        \__/  \__/ f (_)(_)|       */
/*   Updated: 2025/02/09 23:59:54 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error(void)
{
	perror("fail");
	exit(EXIT_FAILURE);
}

void	ft_hook(void *param)
{
	const mlx_t	*mlx = param;

	ft_printf("WIDTH: %d | HEIGHT %d\n", mlx->width, mlx->height);
}

void my_keyhook(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx = param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_terminate(mlx);
    if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
        puts("Key up");
}

void argument_count(int argc)
{
    if (argc != 2 && argc != 4)
    {
        ft_printf("Usage: ./fractol [fern | julia <r> <i> | mandelbrot]\n");
        exit(EXIT_SUCCESS);
    }
}

void my_scrollhook(double xdelta, double ydelta, void *param)
{
    t_mandelbrot		*mlx;
    int x;
    int y;

	mlx = param;
	if (ydelta > 0)
    {
        mlx_get_mouse_pos(mlx->mlx, &x, &y);
        mlx->zoom -= .05;
    }
	else if (ydelta < 0)
    {
        mlx_get_mouse_pos(mlx->mlx, &x, &y);
        mlx->zoom += .05;
    }
	(void)xdelta;
}

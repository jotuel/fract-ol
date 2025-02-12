/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   hook.c                                         __/  \__  i (_(_)(_|(/_   */
/*                                                 /  \__/  \ v  _ _|_        */
/*   By: marvin <marvin@42.fr>                     \__/  \__/ e _>(_| | --    */
/*                                                 /  \__/  \ .  _  _ |       */
/*   Created: 2025/02/08 23:22:09 by marvin        \__/  \__/ f (_)(_)|       */
/*   Updated: 2025/02/12 11:48:57 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
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
    t_mandelbrot *mlx;

    mlx = param;
    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(mlx->mlx);
    if (keydata.key == MLX_KEY_UP)
        mlx->y -= 5;
    if (keydata.key == MLX_KEY_DOWN)
        mlx->y += 5;
    if (keydata.key == MLX_KEY_LEFT)
        mlx->x -= 5;
    if (keydata.key == MLX_KEY_RIGHT)
        mlx->x += 5;
    if (keydata.key == MLX_KEY_SPACE)
    {
        mlx->x = 0;
        mlx->y = 0;
        mlx->zoom = 1.;
    }
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
    mlx_get_mouse_pos(mlx->mlx, &x, &y);
    if (ydelta > 0)
    {
        if (mlx->iter == I_MAX)
            mlx->iter += ydelta;
        mlx->zoom *= 0.99;
        mlx->x =  x / (mlx->zoom * 6);
        mlx->y =  y / (mlx->zoom * 6);
    }
	else
    {
        mlx->zoom *= 1.01;
        mlx->x -= x * (mlx->zoom * 6);
        mlx->y -= y * (mlx->zoom * 6);
    }
    printf("x:%f y:%f", mlx->x, mlx->y);
	(void)xdelta;
}

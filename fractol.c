/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:39:08 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/16 18:16:35 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void ft_error(void) {
    fprintf(stderr, "%s", mlx_strerror(errno));
    exit(EXIT_FAILURE);
}

static void ft_hook(void *param) {
    const mlx_t *mlx = param;

    ft_printf("WIDTH: %d | HEIGHT %d\n", mlx->width, mlx->height);
}

void my_scrollhook(double xdelta, double ydelta, void* param)
{
    mlx_image_t *image;
    image = param;
	// Simple up or down detection.
	if (ydelta > 0)
		puts("Up!");
	else if (ydelta < 0)
		puts("Down!");
    (void)xdelta;
}

int main(int argc, char *argv[]) {
    mlx_t *mlx;
    mlx_image_t *img;

    if(argc != 2) {
      ;
    }
    mlx_set_setting(MLX_FULLSCREEN, true);
    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    mlx = mlx_init(WIDTH, HEIGHT, "Fract'Ol", true);
    if (!mlx)
        ft_error();
    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
        ft_error();
    ft_memset(img->pixels, 0xFF00FFF0, img->width * img->height * sizeof(int32_t));
    mlx_image_to_window(mlx, img, 0, 0);

//    mlx_put_pixel(img, 256, 256, 0xFFFFFF);
    mlx_loop_hook(mlx, ft_hook, mlx);
    if(!ft_strncmp(argv[1], "fern", 5))
            mlx_loop_hook(mlx, &fern_initialize, img);
    else if (!ft_strncmp(argv[1], "julia", 6))
      mlx_loop_hook(mlx, &julia_set, img);
    mlx_scroll_hook(mlx, &my_scrollhook, img);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}

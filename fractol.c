//
// Created by jtuomi on 12/6/24.
//
#include "fractol.h"

#include <string.h>

struct fern_s {
  double x;
  double y;
  double xn;
  double yn;
  double r;
  mlx_image_t *image;
  int color;
  int iter;
  } fern_t;

static void fern_fractal(void *param) {
	double x;
	double y;
	double t;
	double xn;
	double yn;
    double r;
    mlx_image_t *image;
    int iter;

    iter = 0x00FF00FF;
    if(param)
       image = param;
	x = 0.0;
	y = 0.0;
	t = 0.0;
	xn = 0.0;
	yn = 0.0;
	while (t < FITERATIONS)
	{
	r=((double)rand()/(double)RAND_MAX);
	if (r < 0.01)
	{
		xn = 0.0;
		yn = 0.16 * y;
	}
	else if (r < 0.86)
	{
		xn = 0.86 * x + 0.04 * y;
		yn = -0.04 * x + 0.85 * y + 1.6;
	} else if (r < 0.93) {
		xn = 0.2 * x - 0.26 * y;
		yn = 0.23 * x + 0.22 * y + 1.6;
	} else {
		xn = -0.15 * x + 0.28 * y;
		yn = 0.26 * x + 0.24 * y + 0.44;
	}
	mlx_put_pixel(image, xn * 120 + 300, yn * 90, iter++ );
	t += 1;
	y = yn;
	x = xn;
	}
	
}
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

	// Can also detect a mousewheel that goes along the X (e.g: MX Master 3)
	if (xdelta < 0)
		puts("Sliiiide to the left!");
	else if (xdelta > 0)
		puts("Sliiiide to the right!");
}

int main(int argc, char *argv[]) {
    mlx_t *mlx;
    mlx_image_t *img;

    if(argc != 2) {
      ;
    }

    mlx_set_setting(MLX_STRETCH_IMAGE, true);
    mlx_set_setting(MLX_FULLSCREEN, true);
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
            mlx_loop_hook(mlx, &fern_fractal, img);
    else if (!ft_strncmp(argv[1], "julia", 6))
      mlx_loop_hook(mlx, &julia_set, img);
    mlx_scroll_hook(mlx, &my_scrollhook, img);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}

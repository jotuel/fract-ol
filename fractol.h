#ifndef FRACTOL_H
#define FRACTOL_H
#include "lib/include/MLX42/MLX42.h"
#include <complex.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "libft/libft.h"
#define WIDTH 1024
#define HEIGHT 768
#define SCALE_W (WIDTH / 4)
#define SCALE_H (HEIGHT / 4)
#define ITERATIONS 100
#define RADIUS 2.0
#define RADIX RADIUS * 2
#define FITERATIONS 10000000

typedef struct complex_s {
  double complex x;
  double complex y;
} complex_t;

typedef struct fern_s {
  double c;
  double x;
  double xn;
  double y;
  double yn;
  double r;
  mlx_image_t *image;
  int color;
  int iter;
  } fern_t;

void fern_initialize(void *param);
void julia_set(void *param);
typedef void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param);
void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);



#endif

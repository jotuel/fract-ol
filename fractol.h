#ifndef FRACTOL_H
#define FRACTOL_H
#include "libmlx/include/MLX42/MLX42.h"
#include "libmlx/include/MLX42/MLX42_Int.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <tgmath.h>
#include <complex.h>
#include "libft/libft.h"
#define WIDTH 1024
#define HEIGHT 768
#define REN_WID 1024
#define REN_HEI 786
#define SCALE_W (WIDTH / 2)
#define SCALE_H (HEIGHT / 2)
#define ITERATIONS 256
#define RADIUS 2.0
#define RADIX RADIUS * 2
#define FITERATIONS 10000000

typedef struct julia_s {
  double complex c;
  double complex z;
  double tmp;
  double radius;
  mlx_image_t *image;
  int color;
  int iter;
} julia_t;

typedef struct mandelbrot_s {
  double complex c;
  double complex z;
  double complex tmp;
  double complex radius;
  mlx_image_t *image;
  int color;
  int iter;
} mandelbrot_t;

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
void julia_initialize(void *param);
typedef void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param);
void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);
void mandelbrot_initialize(void *param);



#endif

#ifndef FRACTOL_H
#define FRACTOL_H
#include "lib/MLX42/include/MLX42/MLX42.h"
#include <complex.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "libft/libft.h"
#define WIDTH 1080
#define HEIGHT 1080
#define SCALE_W (WIDTH / 2)
#define SCALE_H (HEIGHT / 2)
#define ITERATIONS 1000
#define RADIX 2
#define FITERATIONS 10000000
typedef struct complex_s{
  double x,y;
}  complex_t;



complex_t add(complex_t a,complex_t b);
complex_t sqr(complex_t a);
double mod(complex_t a);
complex_t map_point(int width,int height,double radius,int x,int y);
void julia_set(void *param);
typedef void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param);
void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);
#endif

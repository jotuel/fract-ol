#ifndef FRACTOL_H
#define FRACTOL_H
#include "mlx42.h"
#include <complex.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include "libft/libft.h"

int main(int argc, char **argv);
void fractol(SDL_Renderer *rend, SDL_Window *win);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   fractol.h                                      __/  \__  i (_(_)(_|(/_   */
/*                                                 /  \__/  \ v  _ _|_        */
/*   By: marvin <marvin@42.fr>                     \__/  \__/ e _>(_| | --    */
/*                                                 /  \__/  \ .  _  _ |       */
/*   Created: 2025/02/09 23:45:47 by marvin        \__/  \__/ f (_)(_)|       */
/*   Updated: 2025/02/10 14:24:50 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <complex.h>
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <tgmath.h>
# define WIDTH 800
# define HEIGHT 800
# define ITERATIONS 256
# define RADIUS 2.0
# define RADIX 625
# define FITERATIONS 10000000

typedef struct s_fractol
{
	mlx_t			*mlx;
	double complex	c;
	double complex	z;
	double complex  dc;
	double complex  de;
	double			radius;
	double val;
	double hue;
	double sat;
	double px;
	mlx_image_t		*image;
	int				as_rat;
	int				zoom;
	int				iter;
	int             w;
	int             h;
	int aa;
}					t_fractol;

typedef t_fractol	t_mandelbrot;
typedef t_fractol	t_julia;

typedef struct s_fern
{
	double			c;
	double			x;
	double			xn;
	double			y;
	double			yn;
	double			r;
	mlx_image_t		*image;
	int				color;
	int				iter;
}					t_fern;

void				ft_error(void);
void				ft_hook(void *param);
void				my_keyhook(mlx_key_data_t keydata, void *param);
void				argument_count(int argc);
void				my_scrollhook(double xdelta, double ydelta, void *param);
void				fern_initialize(void *param);
void				julia_initialize(void *param);
void				mlx_scroll_hook(mlx_t *mlx, mlx_scrollfunc func,
						void *param);
void				mandelbrot_initialize(void *param);

inline int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

inline double	cnorm(double complex z)
{
	return (creal(z) * creal(z) + cimag(z) * cimag(z));
}

int case_0(double v, double t, double p);
int case_1(double q, double v, double p);
int case_2(double p, double v, double t);
int case_3(double p, double q, double v);
int case_4(double t, double p, double v);

#endif

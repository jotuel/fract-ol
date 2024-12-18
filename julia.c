#include "fractol.h"

void julia_set(void *param){
    int x;
    int y;
    int i;
	double radius;
    mlx_image_t *image;
    complex_t c;
    complex_t z;
	complex_t tmp;
	double complex radix;
	int color;

	color = 0x000000FF;
	c.x = 0.08;
	c.y = -0.174543;
	x = 0;
	y = 0;
	i = 0;
	image = param;
	radix = RADIUS;
	while(WIDTH > x)
	{
		while(HEIGHT > y)
		{
			z.x = x / SCALE_W - RADIUS;
			z.y = y / SCALE_H - RADIUS;
			while(radius < RADIX && i < ITERATIONS)
			{
				tmp.x = z.x * z.x - z.y * z.y;
				tmp.y = 2 * z.x * z.y;
				z.x = tmp.x + c.x;
				z.y = tmp.y + c.y;
				i++;
				radius = z.x * z.x + z.y * z.y;
			}
		if (i == ITERATIONS)
			mlx_put_pixel(image, x, y, color);
		else
            mlx_put_pixel(image, x, y, (1 - i / ITERATIONS )* 0xFFFFFFFF);
        i = 0;
        y++;
		}
	y = 0;
	x++;
	}
}

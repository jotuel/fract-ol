//
// Created by jtuomi on 12/11/24.
//
#include "fractol.h"



void julia_set(void *param){
    int x;
    int y;
    int i;
    mlx_image_t *image;
    complex_t c;
    complex_t z;
	double tmp;
    double abs_z;
	int color;

	color = 0x000000FF;
	c.x = 0.11301;
	c.y = -0.74543;
	x = 0;
	y = 0;
	i = 0;
	image = param;
	while(WIDTH > x)
	{
		while(HEIGHT > y)
		{
			z.x = x / WIDTH;
			z.y = y / HEIGHT;
			while(z.x * z.x + z.y * z.y < RADIX && i < ITERATIONS)
			{
				tmp = z.x * z.x - z.y * z.y;
				z.y = 2 * z.x * z.y + c.y;
				z.x = tmp + c.x;
				i++;
			}
		if (i == ITERATIONS)
			mlx_put_pixel(image, x, y, color);
		else
        {
			abs_z = z.x * z.x + z.y * z.y;
            mlx_put_pixel(image, x, y, (1 - i / ITERATIONS )* 0xFFFFFFFF);
        }
        i = 0;
        y++;
		}
    y = 0;
	x++;
	}
}

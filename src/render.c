#include "../inc/fractol.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{	
	int offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}


// Mandelbrot: z = z² + c
// 			z initially is (0,0)
// 			c is the actual point

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	int			i;
	int			color;
	t_complex	z;
	t_complex	c;

	i = 0;
	z.x = 0.0;
	z.y = 0.0;

	c.x = map(x, -2, +2, 0, WIDTH);
	c.y = map(y, +2, -2, 0, HEIGHT);

	while (i < fractal->iterations_def)//how many timex the mandelbrot function will be iterated until the point scape
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)//the point has escaped
		{
			color = map(i, BLACK, WHITE, 0, fractal->iterations_def);
			my_pixel_put(x, y, &fractal->img, color);
			return;
		}
		++i;
	}
	//we are in mandelbroth, given the iterations made
	my_pixel_put(x, y, &fractal->img, ELECTRIC_PURPLE);
}

void    fractal_render(t_fractal    *fractal)
{
    int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window, fractal->img.img_ptr, 0, 0);
}

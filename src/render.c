#include "../inc/fractol.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{	
	int offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

// Mandelbrot: 
//	z = z² + c
// 	z initially is (0,0)
// 	c is the actual point

// Julia:
// ./fractol julia <real> <i>
// z = pixel_point + constant
// constant = <real> <i>

static	void mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	int			i;
	int			color;
	t_complex	z;
	t_complex	c;

	i = 0;
	z.x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;

	mandel_vs_julia(&z, &c, fractal);

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
	my_pixel_put(x, y, &fractal->img, WHITE);
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

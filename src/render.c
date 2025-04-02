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

static	void mandel_vs_julia(t_complex *z, t_complex *c, t_fractol *fractol)
{
	if (!ft_strncmp(fractol->name, "julia", 5))
	{
		c->x = fractol->julia_x;
		c->y = fractol->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractol *fractol)
{
	int			i;
	int			color;
	t_complex	z;
	t_complex	c;

	i = 0;
	z.x = (map(x, -2, +2, 0, WIDTH) * fractol->zoom) + fractol->shift_x;
	z.y = (map(y, +2, -2, 0, HEIGHT) * fractol->zoom) + fractol->shift_y;

	mandel_vs_julia(&z, &c, fractol);

	while (i < fractol->iterations_def)//how many timex the mandelbrot function will be iterated until the point scape
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractol->escape_value)//the point has escaped
		{
			color = map(i, BLACK, WHITE, 0, fractol->iterations_def);
			my_pixel_put(x, y, &fractol->img, color);
			return;
		}
		++i;
	}
	//we are in mandelbroth, given the iterations made
	my_pixel_put(x, y, &fractol->img, WHITE);
}

void    fractol_render(t_fractol    *fractol)
{
    int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractol);
		}
	}
	mlx_put_image_to_window(fractol->mlx_connection, fractol->mlx_window, fractol->img.img_ptr, 0, 0);
}

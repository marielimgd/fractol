#include "../inc/fractol.h"

static void	ft_put_pixel(int x, int y, t_img *img, int color)
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
// ./fractal julia <real> <i>
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

static t_complex calculate_initial_z(int x, int y, t_fractal *fractal)
{
    t_complex z;
    double real_min = fractal->shift_x - (2.0 / fractal->zoom);
    double real_max = fractal->shift_x + (2.0 / fractal->zoom);
    double imag_min = fractal->shift_y - (2.0 / fractal->zoom);
    double imag_max = fractal->shift_y + (2.0 / fractal->zoom);

    z.x = real_min + ((real_max - real_min) * x / WIDTH);
    z.y = imag_min + ((imag_max - imag_min) * y / HEIGHT);
    return z;
}

static void handle_pixel(int x, int y, t_fractal *fractal)
{
    int i = 0;
    int color;
    t_complex z, c;
    const int *palette;
    
    palette = get_palette();
    z = calculate_initial_z(x, y, fractal);
    mandel_vs_julia(&z, &c, fractal);
    while (i < fractal->iterations_def)
    {
        z = sum_complex(square_complex(z), c);
        if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
        {
            color = palette[i % 21];
            ft_put_pixel(x, y, &fractal->img, color);
            return;
        }
        ++i;
    }
    ft_put_pixel(x, y, &fractal->img, PLASMA_ROXO);
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

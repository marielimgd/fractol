/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:08:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/03 18:02:16 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

/*
Mandelbrot:
	z = z² + c
	z initially is (0,0)
	c is the actual point
*/

void	calculate_mandelbrot(t_fractal *fractal)
{
	int		i;
	double	tmp;
	double	zx;
	double	zy;

	i = 0;
	zx = 0.0;
	zy = 0.0;
	fractal->name = "mandelbrot";
	fractal->cx = (fractal->x / fractal->zoom) + fractal->offset_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->offset_y;
	while (i < fractal->max_iterations)
	{
		tmp = zx;
		zx = zx * zx - zy * zy + fractal->cx;
		zy = 2.0 * tmp * zy + fractal->cy;
		if (zx * zx + zy * zy > 4.0)
			break ;
		i++;
	}
	if (i == fractal->max_iterations)
		draw_pixel_color(fractal, fractal->x, fractal->y, 0x000000);
	else
		draw_pixel_color(fractal, fractal->x, fractal->y, fractal->color * i);
}

void	draw_mandelbrot(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			fractal->x = x;
			fractal->y = y;
			calculate_mandelbrot(fractal);
			x++;
		}
		y++;
	}
}

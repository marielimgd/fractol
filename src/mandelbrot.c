/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:08:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/03 17:40:34 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/fractol.h"

// Mandelbrot: 
//	z = z² + c
// 	z initially is (0,0)
// 	c is the actual point

void calculate_mandelbrot(t_fractal *fractal)
{
    int i;
    double t, zx, zy;

    fractal->name = "mandel";
    fractal->cx = (fractal->x / fractal->zoom) + fractal->offset_x;
    fractal->cy = (fractal->y / fractal->zoom) + fractal->offset_y;
    zx = 0.0;
    zy = 0.0;
    i = 0;
    while (i < fractal->max_iterations)
    {
        t = zx;
        zx = zx * zx - zy * zy + fractal->cx;
        zy = 2.0 * t * zy + fractal->cy;
        if (zx * zx + zy * zy > 4.0)
            break;
        i++;
    }
    if (i == fractal->max_iterations)
        draw_pixel_color(fractal, fractal->x, fractal->y, 0x000000);
    else
        draw_pixel_color(fractal, fractal->x, fractal->y, fractal->color * i);
}

void draw_mandelbrot(t_fractal *fractal)
{
    int x, y;

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


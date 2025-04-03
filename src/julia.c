/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:08:33 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/03 17:40:32 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

/*
Julia:
	./fractal julia <real> <i>
	z = pixel_point + constant
	constant = <real> <i>
*/

double generate_random_c(void)
{
    return (((double)rand() / RAND_MAX) * 3.0 - 1.5);
}

void set_random_julia(double *cx, double *cy)
{
    *cx = generate_random_c();
    *cy = generate_random_c();
}

void calculate_julia(t_fractal *fractal)
{
    int i;
    double tmp, zx, zy;

    fractal->name = "julia";
    zx = fractal->x / fractal->zoom + fractal->offset_x;
    zy = fractal->y / fractal->zoom + fractal->offset_y;

    i = 0;
    while (i < fractal->max_iterations)
    {
        tmp = zx;
        zx = zx * zx - zy * zy + fractal->cx;
        zy = 2.0 * zy * tmp + fractal->cy;
        if (zx * zx + zy * zy > 4.0)
            break;
        i++;
    }
    if (i == fractal->max_iterations)
        draw_pixel_color(fractal, fractal->x, fractal->y, 0x000000);
    else
        draw_pixel_color(fractal, fractal->x, fractal->y, fractal->color * (i % 255));
}

void draw_julia(t_fractal *fractal)
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
            calculate_julia(fractal);
            x++;
        }
        y++;
    }
}

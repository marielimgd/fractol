/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:35:57 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/03 17:50:22 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	mouse_hook(int mouse_code, int x, int y, t_fractal *fractal)
{
	if (mouse_code == SCROLL_UP)
		zoom(fractal, x, y, 1);
	else if (mouse_code == SCROLL_DOWN)
		zoom(fractal, x, y, -1);
	draw_fractal(fractal, fractal->name);
	return (0);
}

int	key_hook(int key_code, t_fractal *fractal)
{
	if (key_code == XK_Escape)
		exit_fractal(fractal);
	else if (key_code == XK_Left)
		fractal->offset_x -= 42 / fractal->zoom;
	else if (key_code == XK_Right)
		fractal->offset_x += 42 / fractal->zoom;
	else if (key_code == XK_Up)
		fractal->offset_y -= 42 / fractal->zoom;
	else if (key_code == XK_Down)
		fractal->offset_y += 42 / fractal->zoom;
	else if (key_code == XK_r)
		init_fractal(fractal);
	else if (key_code == XK_c)
		fractal->color += (255 * 255 * 255) / 100;
	else if (key_code == XK_j)
		set_random_julia(&fractal->cx, &fractal->cy);
	else if (key_code == XK_m || key_code == XK_p)
		change_iterations(fractal, key_code);
	draw_fractal(fractal, fractal->name);
	return (0);
}

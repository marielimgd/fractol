/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:27:19 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/03 17:36:15 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void init_mlx(t_fractal *fractal)
{
    fractal->mlx = mlx_init();
    fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE, "Fract-ol");
    fractal->image = mlx_new_image(fractal->mlx, SIZE, SIZE);
    fractal->pointer_to_image =(int *) mlx_get_data_addr(fractal->image,
                        &fractal->bits_per_pixel,
                        &fractal->size_line,
                        &fractal->endian);
}


void init_fractal(t_fractal *fractal)
{
    fractal->x = 0;
    fractal->y = 0;
    fractal->color = 0xFCBE11;
    fractal->zoom = 300;
    fractal->offset_x = -1.21;
    fractal->offset_y = -1.21;
    fractal->max_iterations = 42;
}

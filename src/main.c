/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:08:02 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/03 17:43:50 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int main(int argc, char **argv)
{
    t_fractal *fractal;

    if (argc != 2)
    {
        ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    fractal = malloc(sizeof(t_fractal));
    init_fractal(fractal);
    init_mlx(fractal);
    mlx_key_hook(fractal->window, key_hook, fractal);
    mlx_mouse_hook(fractal->window, mouse_hook, fractal);
    mlx_hook(fractal->window, 17, 0L, exit_fractal, fractal); /* fecha ao clicar no X */
    draw_fractal(fractal, argv[1]);
    mlx_loop(fractal->mlx);
    return (0);
}

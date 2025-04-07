/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:13:31 by marieli           #+#    #+#             */
/*   Updated: 2025/04/03 18:25:08 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SIZE 800

# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct s_fractal
{
	char	*name;
	int		x;
	int		y;
	int		color;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		max_iterations;
	void	*mlx;
	void	*window;
	void	*image;
	int		*pointer_to_image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	double	cx;
	double	cy;
}			t_fractal;

void		draw_pixel_color(t_fractal *fractal, int x, int y, int color);
int			exit_fractal(t_fractal *fractal);
double		generate_random_c(void);
void		set_random_julia(double *cx, double *cy);
void		change_iterations(t_fractal *fractal, int key_code);
void		zoom(t_fractal *fractal, int x, int y, int zoom_dir);
int			key_hook(int key_code, t_fractal *fractal);
int			mouse_hook(int mouse_code, int x, int y, t_fractal *fractal);
void		calculate_mandelbrot(t_fractal *fractal);
void		calculate_julia(t_fractal *fractal);
void		init_fractal(t_fractal *fractal);
void		init_mlx(t_fractal *fractal);
void		draw_mandelbrot(t_fractal *fractal);
void		draw_julia(t_fractal *fractal);
int			draw_fractal(t_fractal *fractal, char *query);

#endif
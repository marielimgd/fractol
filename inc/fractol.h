/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:13:31 by marieli           #+#    #+#             */
/*   Updated: 2025/03/20 11:39:48 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H


# include "minilibx-linux/mlx.h"
# include "libft.h" //my functions
# include <stdio.h> //debug
# include <stdlib.h> //malloc, free
# include <unistd.h> //write
# include <math.h>

#define WIDTH	800
#define HEIGHT	800


#define ERROR_MESSAGE \
    "Usage: \n" \
    "\"./fractol mandelbrot\" - Renders the Mandelbrot set.\n" \
    "\"./fractol julia <value 1> <value 2>\" - Renders the Julia set with the given complex numbers.\n" \
    "Example: \"./fractol julia -0.8 0.156\"\n"
    

typedef struct s_img //dados para o mlx_get_data_addr
{
    void    *img_ptr; //pointer to image struct
    void    *pixels_ptr; //points to the actual pixels
    int     bpp; //bits per pixel
    int     endian; //order to use the pixels, not used here
    int     line_len;
}              t_img;

    
typedef struct s_fractal //fractal ID
{
	char	*name;
    void    *mlx_connection; //mlx_init()
    void    *mlx_window; //mlx_new_window
    t_img    img;
	
    
}				t_fractal;









#endif
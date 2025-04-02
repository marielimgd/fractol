/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:13:31 by marieli           #+#    #+#             */
/*   Updated: 2025/04/02 15:58:28 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H


# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h> 
# include "libft/libft.h" //my functions
# include <stdio.h> //debug
# include <stdlib.h> //malloc, free
# include <unistd.h> //write
# include <math.h>

#define WIDTH	800
#define HEIGHT	800

//-----------Colors-----------

#define BLACK               0x000000  // Black
#define WHITE               0xFFFFFF  // White
#define NEON_PINK           0xFF00FF  // Neon pink
#define ELECTRIC_BLUE       0x00FFFF  // Electric blue
#define LIME_GREEN          0x00FF00  // Lime green
#define SUNSET_ORANGE       0xFF4500  // Sunset orange
#define PURPLE_HAZE         0x800080  // Purple haze
#define ELECTRIC_PURPLE     0xBF00FF  // Electric purple
#define CYAN                0x00FFFF  // Cyan
#define MAGENTA             0xFF00FF  // Magenta
#define YELLOW              0xFFFF00  // Yellow
#define HOT_PINK            0xFF69B4  // Hot pink
#define NEON_GREEN          0x39FF14  // Neon green
#define ORANGE              0xFFA500  // Orange
#define DEEP_PURPLE         0x4B0082  // Deep purple
#define AQUA                0x00FFFF  // Aqua
#define GOLD                0xFFD700  // Gold

//---------malloc error----------
#define ERROR_MESSAGE \
    "Usage: \n" \
    "\"./fractol mandelbrot\" - Renders the Mandelbrot set.\n" \
    "\"./fractol julia <value 1> <value 2>\" - Renders the Julia set with the given complex numbers.\n" \
    "Example: \"./fractol julia -0.8 0.156\"\n"

	
//---------Caracteristicas da imagem--------
typedef struct s_img //dados para o mlx_get_data_addr
{
    void    *img_ptr; //pointer to image struct
    void    *pixels_ptr; //points to the actual pixels
    int     bpp; //bits per pixel
    int     endian; //order to use the pixels, not used here
    int     line_len;
}              t_img;


//---------Carcteristicas do fractol----------
typedef struct s_fractol //fractol ID
{
	char	    *name;
    void        *mlx_connection; //mlx_init()
    void        *mlx_window; //mlx_new_window
    t_img       img;
	double	    escape_value; //hipotenusa
	int		    iterations_def; //value tight with the image quality and rendering speed
    double      shift_x;
    double      shift_y;
    double      zoom;
    double      julia_x;
    double      julia_y;
}				t_fractol;


//---------Para fazer os calculos com numeros complexos----------
typedef struct s_complex
{
    double	x; //real number
	double	y; //imaginary number i
}				t_complex;

//------------funções----------------------------
//init:
void        data_init(t_fractol *fractol);
void 	    fractol_init(t_fractol *fractol);

//render:
void        fractol_render(t_fractol    *fractol);

//math:
double 		map(double   unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);

//events:
int         key_handler(int keysym, t_fractol *fractol);
int         close_handler(t_fractol *fractol);
//int         mouse_handler(int button, int x, int y, t_fractol *fractol);
int         julia_track(int x, int y, t_fractol *fractol);

#endif
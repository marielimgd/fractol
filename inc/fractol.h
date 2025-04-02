/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:13:31 by marieli           #+#    #+#             */
/*   Updated: 2025/04/02 18:39:00 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef fractal_H
# define fractal_H


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

#define BLACK            0x000000  // Black
#define CORAL_POP        0xF4785E  // Coral vibrante, inspirado na moda Mod
#define SOL_PSICODELICO  0xF3A35C  // Amarelo intenso, característico do Flower Power
#define RAIO_LIBERDADE   0xF7D47A  // Amarelo pastel suave, usado em cartazes vintage
#define VERDE_HARMONY    0xB1CC9F  // Verde ligado à natureza e ao movimento hippie
#define AGUA_VIVA        0xA5DAD2  // Verde-água futurista, comum em decorações
#define DENIM_RETRO      0x8EB2C5  // Azul jeans clássico, rebelde e icônico
#define MAGENTA_VIBRANTE 0xD13092  // Magenta saturado, essencial para arte psicodélica
#define ROXO_VORTEX      0x7731D1  // Roxo profundo e hipnotizante, típico da estética dos anos 60
#define LARANJA_TRIP     0xE06633  // Laranja vibrante, remanescente de pôsteres psicodélicos
#define VERDE_LIMA       0xA4E200  // Verde ácido, usado para contrastes psicodélicos
#define TURQUESA_FLUX    0x32D4CB  // Azul esverdeado, presente em designs retro-futuristas
#define ROSA_ELETRICO    0xFF33CC  // Rosa neon, chamativo e excêntrico
#define CELESTE_HIPPIE   0x3DAAF2  // Azul celeste saturado, remete ao espírito livre dos anos 60
#define AMARELO_ACIDO    0xFFE600  // Amarelo neon forte, contrastante e intenso
#define VERMELHO_VIBES   0xFF2200  // Vermelho quente e saturado, usado em pôsteres da época
#define ABISMO_AZUL      0x00008B  // Azul escuro e misterioso, representando o fundo do Mandelbrot
#define MAGENTA_ELETRICO 0xD9008D  // Magenta vibrante, semelhante às bordas do fractal
#define VIOLETA_NEBULOSO 0x8B00FF  // Roxo forte, típico da estética psicodélica
#define COSMIC_INDIGO    0x4B0082  // Índigo profundo, dando contraste ao azul
#define ROSA_EXPLOSIVO   0xFF1493  // Rosa intenso, criando um efeito de neon surreal
#define LARANJA_HIPNOTICO 0xE06633 // Laranja vibrante, como visto na transição do fractal
#define VERDE_FLUORESCENTE 0x39FF14 // Verde fluorescente que dá um toque ácido ao fractal
#define PINK_PULSAR      0xFC0FC0  // Pink pulsante, refletindo energia psicodélica
#define AZUL_LUMINOSO    0x1E90FF  // Azul brilhante, trazendo profundidade ao Mandelbrot
#define DOURADO_ESPIRAL  0xFFD700  // Ouro intenso, ideal para realce nos detalhes fractais
#define PLASMA_ROXO      0x6A0DAD  // Roxo plasma, perfeito para efeitos hipnóticos
#define WHITE            0xFFFFFF  // White


//---------malloc error----------
#define ERROR_MESSAGE \
    "Usage: \n" \
    "\"./fractal mandelbrot\" - Renders the Mandelbrot set.\n" \
    "\"./fractal julia <value 1> <value 2>\" - Renders the Julia set with the given complex numbers.\n" \
    "Example: \"./fractal julia -0.8 0.156\"\n"

	
//---------Caracteristicas da imagem--------
typedef struct s_img //dados para o mlx_get_data_addr
{
    void    *img_ptr; //pointer to image struct
    void    *pixels_ptr; //points to the actual pixels
    int     bpp; //bits per pixel
    int     endian; //not used, but some functions require
    int     line_len;
}              t_img;


//---------Carcteristicas do fractal----------
typedef struct s_fractal //fractal ID
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
}				t_fractal;


//---------Para fazer os calculos com numeros complexos----------

typedef struct s_complex
{
    double	x; //real number
	double	y; //imaginary number i
}				t_complex;

// #define SQUARE_COMPLEX(z) (t_complex){(z.x * z.x) - (z.y * z.y), (2 * z.x * z.y)}
// #define SUM_COMPLEX(z1, z2) (t_complex){(z1.x + z2.x), (z1.y + z2.y)}


//------------funções----------------------------
//init:
void        data_init(t_fractal *fractal);
void 	    fractal_init(t_fractal *fractal);

//render:
// const int   *get_palette(void);
void        fractal_render(t_fractal    *fractal);

//math:
double 		map(double   unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);

//events:
int         key_handler(int keysym, t_fractal *fractal);
int         close_handler(t_fractal *fractal);
int         mouse_handler(int button, int x, int y, t_fractal *fractal);
int         julia_track(int x, int y, t_fractal *fractal);

#endif
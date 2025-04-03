/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:13:31 by marieli           #+#    #+#             */
/*   Updated: 2025/04/03 17:43:24 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h> 
# include "libft/libft.h" //my functions
# include <stdio.h> //debug
# include <stdlib.h> //malloc, free
# include <unistd.h> //write
# include <math.h>

// Tamanho da janela (pode ajustar conforme necessário)
#define SIZE 800

#define ERROR_MESSAGE \
    "Usage: \n" \
    "\"./fractol mandelbrot\" - Renders the Mandelbrot set.\n" \
    "\"./fractol julia \" - Renders the Julia set.\n" \
 //   "Example: \"./fractol julia -0.8 0.156\"\n"

// /* 
//    Definições de teclas.
//    Estes valores são exemplos e podem variar dependendo do sistema e configuração.
// */
// #define ESC 65307      // Tecla Escape (usado para sair)
// #define LEFT 65361     // Tecla seta para a esquerda
// #define RIGHT 65363    // Tecla seta para a direita
// #define UP 65362       // Tecla seta para cima
// #define DOWN 65364     // Tecla seta para baixo
// #define R 114          // Tecla 'r' para resetar o fractal
// #define C 99           // Tecla 'c' para mudar a cor
// #define J 106          // Tecla 'j' para alterar parâmetros do Julia
// #define M 109          // Tecla 'm' para diminuir iterações
// #define P 112          // Tecla 'p' para aumentar iterações

/* Definições para eventos do mouse (códigos típicos para MiniLibX) */
#define SCROLL_UP 4
#define SCROLL_DOWN 5

// /*  
//    Definições das cores da paleta (baseadas na estética psicodélica)
//    São 22 cores conforme seu projeto.
// */
// #define CORAL_POP         0xF4785E
// #define SOL_PSICODELICO   0xF3A35C
// #define RAIO_LIBERDADE    0xF7D47A
// #define VERDE_HARMONY     0xB1CC9F
// #define AGUA_VIVA         0xA5DAD2
// #define DENIM_RETRO       0x8EB2C5
// #define MAGENTA_VIBRANTE  0xD13092
// #define ROXO_VORTEX       0x7731D1
// #define LARANJA_TRIP      0xE06633
// #define VERDE_LIMA        0xA4E200
// #define TURQUESA_FLUX     0x32D4CB
// #define ROSA_ELETRICO     0xFF33CC
// #define CELESTE_HIPPIE    0x3DAAF2
// #define AMARELO_ACIDO     0xFFE600
// #define VERMELHO_VIBES    0xFF2200
// #define ABISMO_AZUL       0x00008B
// #define MAGENTA_ELETRICO  0xD9008D
// #define VIOLETA_NEBULOSO  0x8B00FF
// #define COSMIC_INDIGO     0x4B0082
// #define ROSA_EXPLOSIVO    0xFF1493
// #define LARANJA_HIPNOTICO 0xE06633
// #define VERDE_FLUORESCENTE 0x39FF14

// // Cor default para pontos que não escapam
// #define PLASMA_ROXO       0x6A0DAD

/**
 * Estrutura que armazena os parâmetros e recursos do fractal.
 */
typedef struct s_fractal
{
    char    *name; // Nome do fractal ("mandel" ou "julia")
    /* Parâmetros de iteracão e renderização */
    int     x;              // Coordenada x do pixel atual
    int     y;              // Coordenada y do pixel atual
    int     color;          // Fator base para cálculo de cor
    double  zoom;           // Nível de zoom
    double  offset_x;       // Deslocamento horizontal no plano
    double  offset_y;       // Deslocamento vertical no plano
    int     max_iterations; // Número máximo de iterações

    /* Recursos da MiniLibX */
    void    *mlx;           // Conexão com o servidor MLX
    void    *window;        // Janela criada
    void    *image;         // Imagem criada para desenhar o fractal
    int     *pointer_to_image; // Buffer de pixels da imagem
    int     bits_per_pixel; // Bits por pixel na imagem
    int     size_line;      // Tamanho de cada linha do buffer (em bytes)
    int     endian;         // Endianness da imagem

    /* Parâmetros específicos para o conjunto de Julia */
    double  cx;             // Constante real
    double  cy;             // Constante imaginária
}           t_fractal;

// // Funções de manipulação/de desenho de pixels e imagens
void    draw_pixel_color(t_fractal *fractal, int x, int y, int color);
int     exit_fractal(t_fractal *fractal);

// // Funções auxiliares
double  generate_random_c(void);
void    set_random_julia(double *cx, double *cy);
void    change_iterations(t_fractal *fractal, int key_code);
void    zoom(t_fractal *fractal, int x, int y, int zoom_dir);

// // Handlers de eventos
int     key_hook(int key_code, t_fractal *fractal);
int     mouse_hook(int mouse_code, int x, int y, t_fractal *fractal);

// // Funções para o cálculo dos fractais
void    calculate_mandelbrot(t_fractal *fractal);
void    calculate_julia(t_fractal *fractal);

// // Funções de inicialização
void    init_fractal(t_fractal *fractal);
void    init_mlx(t_fractal *fractal);

// // Funções de desenho do fractal
void    draw_mandelbrot(t_fractal *fractal);
void    draw_julia(t_fractal *fractal);
int     draw_fractal(t_fractal *fractal, char *query);

#endif
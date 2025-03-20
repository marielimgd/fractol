#include "../inc/fractol.h"

static void    malloc_error(void)
{
    perror("Malloc is not mallocing");
    exit(EXIT_FAILURE);
}

void    data_init(t_fractal *fractal)
{
    fractal->escape_value = 4; //2²
    fractal->iterations_def = 42; 
}

void fractal_init(t_fractal *fractal)
{
    //iniciando a conexão com o servidor
    fractal->mlx_connection = mlx_init();
    if (NULL == fractal->mlx_connection)
        malloc_error(); //todo


    //criando a janela
    fractal->mlx_window = mlx_new_window(fractal->mlx_connection, WIDTH, HEIGHT, fractal->name);
    if (NULL == fractal->mlx_window)
    {
        mlx_destroy_display(fractal->mlx_connection);
        free(fractal->mlx_connection);
        malloc_error();
    }

    //criando a imagem
    fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT);
    if (NULL == fractal->img.img_ptr)
    {
        mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
        mlx_destroy_display(fractal->mlx_connection);
        free(fractal->mlx_connection);
        malloc_error();
    }
    fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);


    //iniciando o evento
    //events_init(fractal)// a funçao mlx_hook deixa a janela aberta e aguarda pelos comandos
    data_init(fractal); //zoom, shift

}

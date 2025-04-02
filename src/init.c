#include "../inc/fractol.h"

void error_exit(const char *message, t_fractol *fractal)
{
    ft_printf( "Erro: %s\nDetalhes: %s\n", message);

    if (fractal->mlx_connection)
    {
        if (fractal->img.img_ptr)
            mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
        if (fractal->mlx_window)
            mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
        mlx_destroy_display(fractal->mlx_connection);
        free(fractal->mlx_connection);
    }

    exit(EXIT_FAILURE);
}


void    data_init(t_fractol *fractol)
{
    fractol->escape_value = 4; //2²
    fractol->iterations_def = 42; 
    fractol->shift_x = 0;
    fractol->shift_y = 0;
    fractol->zoom = 1.0;

}

static void events_init(t_fractol *fractol)
{
    mlx_hook(fractol->mlx_window, KeyPress, KeyPressMask, key_handler, fractol);
    // mlx_hook(fractol->mlx_window, ButtonPress, ButtonPressMask, mouse_handler, fractol);
    mlx_hook(fractol->mlx_window, DestroyNotify, StructureNotifyMask, close_handler, fractol); //fecha a janela quando aperta o x
    mlx_hook(fractol->mlx_window, MotionNotify, PointerMotionMask, julia_track, fractol); //fecha a janela quando aperta o x

}

void fractol_init(t_fractol *fractol)
{
    //iniciando a conexão com o servidor
    fractol->mlx_connection = mlx_init();
    if (NULL == fractol->mlx_connection)
        error_exit("Falha ao inicializar MiniLibX", fractol);


    //criando a janela
    fractol->mlx_window = mlx_new_window(fractol->mlx_connection, WIDTH, HEIGHT, fractol->name);
    if (NULL == fractol->mlx_window)
    {
        mlx_destroy_display(fractol->mlx_connection);
        free(fractol->mlx_connection);
        error_exit("Falha ao criar janela", fractol);
    }

    //criando a imagem
    fractol->img.img_ptr = mlx_new_image(fractol->mlx_connection, WIDTH, HEIGHT);
    if (NULL == fractol->img.img_ptr)
    {
        mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
        mlx_destroy_display(fractol->mlx_connection);
        free(fractol->mlx_connection);
        error_exit("Falha ao criar imagem", fractol);
    }
    fractol->img.pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr, &fractol->img.bpp, &fractol->img.line_len, &fractol->img.endian);


    //iniciando o evento
    events_init(fractol);// a funçao mlx_hook deixa a janela aberta e aguarda pelos comandos
    data_init(fractol); //zoom, shift

}

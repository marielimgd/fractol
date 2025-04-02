#include "../inc/fractol.h"

void error_exit(const char *message, t_fractal *fractal)
{
    ft_printf( "Erro: %s\nDetalhes: %s\n", message);

    if (fractal)
    {    if (fractal->mlx_connection)
        {
            if (fractal->img.img_ptr)
                mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
            if (fractal->mlx_window)
                mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
            mlx_destroy_display(fractal->mlx_connection);
            free(fractal->mlx_connection);
        }
    }
    exit(EXIT_FAILURE);
}


void    data_init(t_fractal *fractal)
{
    if (!fractal)
        return;
    fractal->escape_value = 4; //2²
    fractal->iterations_def = 42; 
    fractal->shift_x = 0;
    fractal->shift_y = 0;
    fractal->zoom = 1.0;

}

static void events_init(t_fractal *fractal)
{
    if (!fractal || !fractal->mlx_window)
        return;
    ft_printf("Registrando eventos...\n");
    mlx_hook(fractal->mlx_window, KeyPress, KeyPressMask, key_handler, fractal);
    mlx_hook(fractal->mlx_window, ButtonPress, ButtonPressMask, mouse_handler, fractal);
    mlx_hook(fractal->mlx_window, DestroyNotify, StructureNotifyMask, close_handler, fractal); //fecha a janela quando aperta o x
    mlx_hook(fractal->mlx_window, MotionNotify, PointerMotionMask, julia_track, fractal); //fecha a janela quando aperta o x
    ft_printf("Eventos registrados!\n");
}

void fractal_init(t_fractal *fractal)
{
    if (!fractal)
        error_exit("Fractal structure is NULL", NULL);
    fractal->mlx_connection = mlx_init(); //iniciando a conexão com o servidor
    if (NULL == fractal->mlx_connection)
        error_exit("Falha ao inicializar MiniLibX", fractal);
    ft_printf("Passou pela inicialização...\n");
    fractal->mlx_window = mlx_new_window(fractal->mlx_connection, WIDTH, HEIGHT, fractal->name);
    if (NULL == fractal->mlx_window)
    {
        mlx_destroy_display(fractal->mlx_connection);
        free(fractal->mlx_connection);
        error_exit("Falha ao criar janela", fractal);
    }
    ft_printf("Criando janela...\n");
    fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT);
    if (NULL == fractal->img.img_ptr)
    {
        mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
        mlx_destroy_display(fractal->mlx_connection);
        free(fractal->mlx_connection);
        error_exit("Falha ao criar imagem", fractal);
    }
    ft_printf("Criando imagem...\n");
    fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr, &fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
    events_init(fractal);// a funçao mlx_hook deixa a janela aberta e aguarda pelos comandos
    data_init(fractal); //zoom, shift, keyboard shortcuts
}

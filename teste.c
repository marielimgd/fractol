#include "teste.h"


/*  
    --------------------------------------------------------------------------------
    Função para pintar o pixel
    --------------------------------------------------------------------------------
*/
void put_color_to_pixel(t_fractal *fractal, int x, int y, int color)
{
    int *buffer;

    buffer = fractal->pointer_to_image;
    /* Cada pixel ocupa 4 bytes; usei /4 para converter em índice de int */
    buffer[(y * fractal->size_line / 4) + x] = color;
}

/*  
    --------------------------------------------------------------------------------
    Função de saída do programa
    --------------------------------------------------------------------------------
*/
int exit_fractal(t_fractal *fractal)
{
    mlx_destroy_image(fractal->mlx, fractal->image);
    mlx_destroy_window(fractal->mlx, fractal->window);
    free(fractal->mlx);
    free(fractal);
    exit(1);
    return (0);
}

/*  
    --------------------------------------------------------------------------------
    Gera um valor aleatório para os parâmetros do Julia
    --------------------------------------------------------------------------------
*/
double generate_random_c(void)
{
    return (((double)rand() / RAND_MAX) * 3.0 - 1.5);
}

/*  
    --------------------------------------------------------------------------------
    Altera o número máximo de iterações (aumenta ou diminui)
    --------------------------------------------------------------------------------
*/
void change_iterations(t_fractal *fractal, int key_code)
{
    if (key_code == M)
    {
        if (fractal->max_iterations > 42)
            fractal->max_iterations -= 42;
    }
    else if (key_code == P)
    {
        if (fractal->max_iterations < 4200)
            fractal->max_iterations += 42;
    }
}

/*  
    --------------------------------------------------------------------------------
    Função de Zoom: re-centra o fractal com base na posição do mouse
    --------------------------------------------------------------------------------
*/
void zoom(t_fractal *fractal, int x, int y, int zoom_dir)
{
    double zoom_level = 1.42;
    
    if (zoom_dir == 1)  // zoom in
    {
        fractal->offset_x = (x / fractal->zoom + fractal->offset_x) -
                            (x / (fractal->zoom * zoom_level));
        fractal->offset_y = (y / fractal->zoom + fractal->offset_y) -
                            (y / (fractal->zoom * zoom_level));
        fractal->zoom *= zoom_level;
    }
    else if (zoom_dir == -1)  // zoom out
    {
        fractal->offset_x = (x / fractal->zoom + fractal->offset_x) -
                            (x / (fractal->zoom / zoom_level));
        fractal->offset_y = (y / fractal->zoom + fractal->offset_y) -
                            (y / (fractal->zoom / zoom_level));
        fractal->zoom /= zoom_level;
    }
}

/*  
    --------------------------------------------------------------------------------
    Seta valores aleatórios para os parâmetros do Julia
    --------------------------------------------------------------------------------
*/
void set_random_julia(double *cx, double *cy)
{
    *cx = generate_random_c();
    *cy = generate_random_c();
}

/*  
    --------------------------------------------------------------------------------
    Tratamento de teclas
    --------------------------------------------------------------------------------
*/
int key_hook(int key_code, t_fractal *fractal)
{
    if (key_code == XK_Escape)
        exit_fractal(fractal);
    else if (key_code == XK_Left)
        fractal->offset_x -= 42 / fractal->zoom;
    else if (key_code == XK_Right)
        fractal->offset_x += 42 / fractal->zoom;
    else if (key_code == XK_Up)
        fractal->offset_y -= 42 / fractal->zoom;
    else if (key_code == XK_Down)
        fractal->offset_y += 42 / fractal->zoom;
    else if (key_code == XK_r)
        init_fractal(fractal);
    else if (key_code == XK_c)
        fractal->color += (255 * 255 * 255) / 100;
    else if (key_code == XK_j)
        set_random_julia(&fractal->cx, &fractal->cy);
    else if (key_code == XK_m || key_code == XK_p)
        change_iterations(fractal, key_code);
    
    draw_fractal(fractal, fractal->name);
    return (0);
}

/*  
    --------------------------------------------------------------------------------
    Tratamento de eventos do mouse (zoom)
    --------------------------------------------------------------------------------
*/
int mouse_hook(int mouse_code, int x, int y, t_fractal *fractal)
{
    if (mouse_code == SCROLL_UP)
        zoom(fractal, x, y, 1);
    else if (mouse_code == SCROLL_DOWN)
        zoom(fractal, x, y, -1);
    
    draw_fractal(fractal, fractal->name);
    return (0);
}

/*  
    --------------------------------------------------------------------------------
    Cálculo do Mandelbrot usando variáveis locais
    --------------------------------------------------------------------------------
*/
void calculate_mandelbrot(t_fractal *fractal)
{
    int i;
    double t, zx, zy;

    fractal->name = "mandel";
    fractal->cx = (fractal->x / fractal->zoom) + fractal->offset_x;
    fractal->cy = (fractal->y / fractal->zoom) + fractal->offset_y;
    zx = 0.0;
    zy = 0.0;
    i = 0;
    while (i < fractal->max_iterations)
    {
        t = zx;
        zx = zx * zx - zy * zy + fractal->cx;
        zy = 2.0 * t * zy + fractal->cy;
        if (zx * zx + zy * zy > 4.0)
            break;
        i++;
    }
    if (i == fractal->max_iterations)
        put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
    else
        put_color_to_pixel(fractal, fractal->x, fractal->y, fractal->color * i);
}


/*  
    --------------------------------------------------------------------------------
    Cálculo do Julia usando variáveis locais
    --------------------------------------------------------------------------------
*/
void calculate_julia(t_fractal *fractal)
{
    int i;
    double tmp, zx, zy;

    fractal->name = "julia";
    zx = fractal->x / fractal->zoom + fractal->offset_x;
    zy = fractal->y / fractal->zoom + fractal->offset_y;

    i = 0;
    while (i < fractal->max_iterations)
    {
        tmp = zx;
        zx = zx * zx - zy * zy + fractal->cx;
        zy = 2.0 * zy * tmp + fractal->cy;
        if (zx * zx + zy * zy > 4.0)
            break;
        i++;
    }
    if (i == fractal->max_iterations)
        put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
    else
        put_color_to_pixel(fractal, fractal->x, fractal->y, fractal->color * (i % 255));
}


/*  
    --------------------------------------------------------------------------------
    Inicializa os parâmetros básicos do fractal
    --------------------------------------------------------------------------------
*/
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

/*  
    --------------------------------------------------------------------------------
    Inicializa a MiniLibX e cria a janela e a imagem
    --------------------------------------------------------------------------------
*/
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

/*  
    --------------------------------------------------------------------------------
    Desenha o Mandelbrot (iterando sobre cada pixel)
    --------------------------------------------------------------------------------
*/
void draw_mandelbrot(t_fractal *fractal)
{
    int x, y;

    y = 0;
    while (y < SIZE)
    {
        x = 0;
        while (x < SIZE)
        {
            fractal->x = x;
            fractal->y = y;
            calculate_mandelbrot(fractal);
            x++;
        }
        y++;
    }
}


/*  
    --------------------------------------------------------------------------------
    Desenha o Julia (iterando sobre cada pixel)
    --------------------------------------------------------------------------------
*/
void draw_julia(t_fractal *fractal)
{
    int x, y;

    y = 0;
    while (y < SIZE)
    {
        x = 0;
        while (x < SIZE)
        {
            fractal->x = x;
            fractal->y = y;
            calculate_julia(fractal);
            x++;
        }
        y++;
    }
}


/*  
    --------------------------------------------------------------------------------
    Função para selecionar qual fractal desenhar (excluindo Burning Ship)
    --------------------------------------------------------------------------------
*/
int draw_fractal(t_fractal *fractal, char *query)
{
    if (ft_strncmp(query, "mandel", 7) == 0)
        draw_mandelbrot(fractal);
    else if (ft_strncmp(query, "julia", 6) == 0)
    {
        /* Se os parâmetros de Julia não estão definidos, usa valores-padrão */
        if (!fractal->cx && !fractal->cy)
        {
            fractal->cx = -0.745429;
            fractal->cy =  0.05;
        }
        draw_julia(fractal);
    }
    else
    {
        ft_putendl_fd("Available fractals: mandel, julia", 1);
        exit_fractal(fractal);
    }
    mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0, 0);
    return (0);
}

/*  
    --------------------------------------------------------------------------------
    Função principal: inicializa estrutura, MLX e entra no loop de eventos
    --------------------------------------------------------------------------------
*/
int main(int argc, char **argv)
{
    t_fractal *fractal;

    if (argc != 2)
    {
        ft_putendl_fd("Usage: ./fractol <fractal>", 1);
        ft_putendl_fd("Available fractals: mandelbrot, julia", 1);
        return (0);
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

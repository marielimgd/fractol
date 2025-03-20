#include "../inc/fractol.h"

int main(int argc, char **argv)
{
    t_fractal    fractal;


    if((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))  
        || (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
    {        
        fractal.name = argv[1];
        fractal_init(&fractal);
        fractal_render(&fractal);
        mlx_loop(fractal.mlx_connection);
    }
    else
    {
        ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }

}
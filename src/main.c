#include "../inc/fractol.h"

int main(int argc, char **argv)
{
    t_fractol    fractol;


    if((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))  
        || (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
    {        
        fractol.name = argv[1];
        fractol.julia_x = ft_atodbl(argv[2]);
        fractol.julia_y = ft_atodbl(argv[3]);
        fractol_init(&fractol);
        fractol_render(&fractol);
        mlx_loop(fractol.mlx_connection);
    }
    else
    {
        ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }

}
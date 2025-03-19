#include "../inc/fractol.h"

int main(int argc, char **argv)
{
    if((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))  || (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
    {

    }
    else
    {
        ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }

}
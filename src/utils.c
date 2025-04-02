#include "../inc/fractol.h"

//rescaling - change the parameters because norminette won allow 5 parametes - can delete old_min assuming that is 0
double map(double   unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return(new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}

t_complex   sum_complex(t_complex z1, t_complex z2)
{
    t_complex   result;

    result.x = z1.x + z2.x;
    result.y = z1.y + z2.y;
    return (result);
}
//real = (x² - y²) | i = 2*x*y
t_complex   square_complex(t_complex z)
{
    t_complex   result;

    result.x = (z.x *z.x) - (z.y * z.y);
    result.y = 2 * z.x * z.y;
    return (result);
}

const int *get_palette(void)
{
    static int palette[21]; 

    palette[0]  = CORAL_POP;
    palette[1]  = SOL_PSICODELICO;
    palette[2]  = RAIO_LIBERDADE;
    palette[3]  = VERDE_HARMONY;
    palette[4]  = AGUA_VIVA;
    palette[5]  = DENIM_RETRO;
    palette[6]  = MAGENTA_VIBRANTE;
    palette[7]  = ROXO_VORTEX;
    palette[8]  = LARANJA_TRIP;
    palette[9]  = VERDE_LIMA;
    palette[10] = TURQUESA_FLUX;
    palette[11] = ROSA_ELETRICO;
    palette[12] = CELESTE_HIPPIE;
    palette[13] = AMARELO_ACIDO;
    palette[14] = VERMELHO_VIBES;
    palette[15] = ABISMO_AZUL;
    palette[16] = MAGENTA_ELETRICO;
    palette[17] = VIOLETA_NEBULOSO;
    palette[18] = COSMIC_INDIGO;
    palette[19] = ROSA_EXPLOSIVO;
    palette[20] = LARANJA_HIPNOTICO;
    palette[21] = VERDE_FLUORESCENTE;
    return (palette);
}

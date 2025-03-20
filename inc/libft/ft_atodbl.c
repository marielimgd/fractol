/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atodbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:42:04 by marieli           #+#    #+#             */
/*   Updated: 2025/03/20 18:04:28 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double  ft_atodbl(char *str)
{
    long    integer;
    double  fraction;
    double  pow;
    int     sign;

    integer = 0;
    fraction = 0;
    sign = +1;
    pow = 1;

    while ((*str && *str >= '0' && *str <= '9') || *str == 32)
        ++str;
    while (*str == '-' || *str == '+') 
        if (*str++ == '-')
            sign = -sign;
    while (*str != '.' && *str)
        integer = (integer * 10) + (*str++ - 48);
    if (*str == '.')
        ++str;
    while (*str)
    {
        pow /= 10;
        fraction = fraction + (*str++ - 48) * pow;
    }
    return ((integer + fraction) * sign);
}

#include "libft.h"

void    ft_strcap(char *str)
{
    int             i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = ft_toupper(str[i]);
        i++;
    }
}

#include "ft_shell.h"

char    **ft_strdup_2(char **src)
{
    int     i;
	char	**new_dest;

	new_dest = NULL;
    i = 0;
    while (src[i])
        i++;
    new_dest = (char **)malloc(sizeof(char *) * (i + 1));
	ft_bzero(new_dest, i + 1);
    i = 0;
    while (src[i])
    {
		new_dest[i] = NULL;
        new_dest[i] = ft_strdup(src[i]);
        i++;
    }
    new_dest[i] = NULL;
    return (new_dest);
}

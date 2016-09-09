/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 09:29:32 by tmack             #+#    #+#             */
/*   Updated: 2016/09/07 13:35:50 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"


void	ft_put_string1(t_shell *s)
{
    int		j;
    int		i;

    i = -1;
    j = 0;
    while (++i < s->curs_col)
        tputs(tgetstr("up", 0), 1, ft_putchar_re);
    tputs(tgetstr("cr", 0), 1, ft_putchar_re);
    tputs(tgetstr("cd", 0), 1, ft_putchar_re);
    ft_prompt_print(s);
    i = 0;
    while (s->new_line[i])
    {
        if (i > (s->cpy_nbr - s->a) && i <= s->cpy_nbr)
        {
            tputs(tgetstr("so", 0), 1, ft_putchar_re);
            ft_putchar(s->new_line[i]);
            tputs(tgetstr("se", 0), 1, ft_putchar_re);
            j++;
            i++;
            continue ;
        }
        ft_putchar(s->new_line[i]);
        i++;
    }
}

void	ft_high_right(t_shell *s, char *buff)
{
    //	if (buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 67)
    if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
            && buff[4] == 53 && buff[5] == 67)
    {
        s->cpy_nbr = s->curs_pos;
        s->a++;
        s->on = 1;
        ft_move_right(s, "A");
        s->on = 0;
        tputs(tgetstr("sc", 0), 1, ft_putchar_re);
        ft_put_string1(s);
        tputs(tgetstr("rc", 0), 1, ft_putchar_re);
    }
}

void    ft_paste_1(t_shell *s, char *new_line)
{
    int     j;
    int     k;

    k = 0;
    j = 0;
    
    while (j <= (s->str_len + s->a))
    {
        if (j == s->curs_pos - 1)
        {
            while (s->cpy_cut[k])
            {
                new_line[j] = s->cpy_cut[k];
                k++;
                j++;
            }
        }
             new_line[j] = s->new_line[j];
        j++;
    }
}

void	ft_paste(t_shell *s, char *buff)
{
    char	*new_line;

    new_line = NULL;
    //if (buff[0] == -53 && buff[1] == -121 && buff[2] == 0 && buff[3] == 0)
    if (buff[0] == 22 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
    {
        new_line = ft_strnew(s->str_len + s->a + 1);
        ft_bzero(new_line, s->str_len + s->a + 1);
        ft_paste_1(s, new_line);
        free(s->new_line);
        s->new_line = ft_strdup(new_line);
        tputs(tgetstr("sc", 0), 1, ft_putchar_re);
        ft_put_string(s);
        tputs(tgetstr("rc", 0), 1, ft_putchar_re);
        s->str_len = ft_strlen(s->new_line);
        ft_strdel(&new_line);
        s->a = 0;
        s->cpy_nbr = 0;
    }
}

void    ft_cpy(t_shell *s, char *buff)
{
    int     j;
    int     k;

    j = 0;
    k = -1;
    if (buff[0] == 24 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
    {
        if (s->cpy_cut != NULL)
            free(s->cpy_cut);
        s->cpy_cut = (char *)malloc(sizeof(char) * s->a + 1);
        ft_bzero(s->cpy_cut, s->a + 1);
        while (j < s->str_len + 1)
        {
            if (j == s->cpy_nbr - s->a)
                while (++k <= s->a)
                {
                    s->cpy_cut[k] = s->new_line[j];
                    j++;
                }
            j++;
        }
    }
}


void    ft_cut(t_shell *s, char *buff)
{
    char    *new_line;
    int     i;
    int     j;
    int     k;

    k = 0;
    i = 0;
    j = 0;
    if (buff[0] == 24 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
    {
        if (s->cpy_cut != NULL)
            free(s->cpy_cut);
        s->cpy_cut = ft_strnew(s->a + 1);
        ft_bzero(s->cpy_cut, s->a + 1);
        new_line = ft_strnew(s->str_len - s->a);
        ft_bzero(new_line, s->str_len - s->a);
        j = 0;
        while (j < s->str_len + 1)
        {
            if (j == (s->cpy_nbr - s->a))
                while (k <= s->a)
                {
                    s->cpy_cut[k] = s->new_line[j];
                    j++;
                    k++;
                }
            new_line[i] = s->new_line[j];
            i++;
            j++;
        }
        free(s->new_line);
        s->new_line = ft_strdup(new_line);
        tputs(tgetstr("sc", 0), 1, ft_putchar_re);
        ft_put_string(s);
        tputs(tgetstr("rc", 0), 1, ft_putchar_re);
        i = -1;
        while (++i <= s->a)
            tputs(tgetstr("le", 0), 1, ft_putchar_re);
        s->curs_pos = s->curs_pos - s->a;
        s->str_len = ft_strlen(s->new_line) + 1;
        ft_strdel(&new_line);
    }

}


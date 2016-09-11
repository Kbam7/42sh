/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:29:52 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/10 20:28:26 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		shell_loop(t_shell *s)
{
	int			ret;
	t_cmd_list	*cmd_list;

	ret = 0;
	while (ret != EXIT_SH)
	{
//		set_prompt(s);
		while (s->commands == NULL)
			buffer(s);
		cmd_list = s->commands;
		while (cmd_list != NULL)
		{
			tputs(tgetstr("cr", 0), 1, ft_putchar_re);
			tputs(tgetstr("ce", 0), 1, ft_putchar_re);
			ret = process_input(cmd_list->cmd, s);
			if (ret == EXIT_SH || ret == EXIT_FAILURE)
			{
				ft_prompt_print(s);
				break ;
			}
			ft_sleep(0, 10000000);
			ft_prompt_print(s);
			cmd_list = cmd_list->next;
		}
		free_cmd_list(&s->commands);
	}
}

static void	ft_exit(t_shell *s)
{
	char	*tmp;

	if ((tmp = ft_getenv("42SH_PID", s)) != NULL && ft_isint(tmp))
	{
		if (getpid() == ft_atoi(tmp))
		{
			tputs(tgetstr("ve", 0), 1, ft_putchar_re);
			tputs(tgetstr("te", 0), 1, ft_putchar_re);
			tcsetattr(STDIN_FILENO, TCSADRAIN, &s->default_term);
		}
	}
	else
	{
		tputs(tgetstr("ve", 0), 1, ft_putchar_re);
		tputs(tgetstr("te", 0), 1, ft_putchar_re);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &s->default_term);
	}
}

void			free_t_shell(t_shell *s)
{
    if (s->history != NULL)
        free_tab((void ***)&s->history, ft_tablen(s->history));
	if (s->commands != NULL)
		free_cmd_list(&s->commands);
	if (s->input != NULL)
		free_tab((void ***)&s->input, ft_tablen(s->input));
	if (s->pipe.pipes != NULL)
		free_tab((void ***)&s->pipe.pipes, (s->pipe.n_pipes + s->pipe.pipe_i));
	if (s->redir.rdr != NULL)
		free_tab((void ***)&s->redir.rdr, ft_tablen(s->redir.rdr));
	if (s->redir.cmd != NULL)
		free_tab((void ***)&s->redir.cmd, ft_tablen(s->redir.cmd));
	free_tab((void ***)&s->paths, ft_tablen(s->paths));
	free_tab((void ***)&s->argv, ft_tablen(s->argv));
	ft_strdel(&s->prompt);
	ft_strdel(&s->curr);
    ft_strdel(&s->new_line);
	ft_exit(s);
	free_tab((void ***)&s->env_var, ft_tablen(s->env_var));
	free_tab((void ***)&s->shell_var, ft_tablen(s->shell_var));
}

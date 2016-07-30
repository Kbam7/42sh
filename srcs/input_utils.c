#include "ft_shell.h"

int	check_colon(char *str, t_shell *s)
{
	int				i;
	int				ret;
	t_split_string	cmds;

	i = -1;
	ret = EXIT_FAILURE;
	if (ft_strchr(str, ';'))
	{
		cmds = ft_nstrsplit(str, ';');
		while (i++ < (int)cmds.words)
			ret = add_cmd(&s->commands, cmds.strings[i]);
		free_tab(cmds.strings, cmds.words);
	}
	else
		ret = add_cmd(&s->commands, str);
	return (ret);
}

int	check_pipe(t_cmd_list **cmd)
{
	int				i;
	int				ret;
	t_split_string	args;
	t_cmd_list		*pipes;

	i = -1;
	args = ft_nstrsplit((*cmd)->cmd, '|');
	if (args.words > 1)
	{
		while (++i < (int)args.words)
			ret = add_cmd(&(*cmd)->pipes, args.strings[i]);
		pipes = (*cmd)->pipes;
		while (pipes)
		{
			if (ft_strchr(pipes->cmd, '<') || ft_strchr(pipes->cmd, '>'))
	//			check_redirect(&pipes, s);
			pipes = pipes->next;
		}
		return (ret);
	}
	else
		return (err(ERR_INVALID_PIPE, "--- check_pipe()---"));
}
/*
int	check_redirect(t_cmd_list *cmd, t_shell *s)
{
	int	i;

	i = 0;
	while (cmd->cmd[i] != '\0')
	{
		if (cmd->cmd[i] == '>')
			check_write
		if (cmd->cmd[i] == '<')
		
	}
}
*/

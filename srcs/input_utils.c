#include "ft_shell.h"

int	store_commands(char *str, t_shell *s)
{
	size_t			i;
	int				ret;
	t_split_string	args;

	i = 0;
	ret = EXIT_FAILURE;
	if (ft_strchr(str, ';'))
	{
		args = ft_nstrsplit(str, ';');
		while (i < args.words)
		{
			ret = add_cmd(&s->commands, args.strings[i]);
			++i;
		}
		free_tab(args.strings, args.words);
	}
	else
		ret = add_cmd(&s->commands, str);
	return (ret);
}
/*
int	store_pipe(t_cmd_list **cmd)
{
	size_t			i;
	int				ret;
	t_split_string	args;
	t_cmd_list		*pipes;

	i = 0;
	args = ft_nstrsplit((*cmd)->cmd, '|');
	if (args.words > 1)
	{
		while (i < args.words)
		{
			ret = add_cmd(&(*cmd)->pipes, args.strings[i]);
			++i;
		}
		return (ret);
	}
	else
		return (err(ERR_INVALID_PIPE, "--- store_pipe()---"));
}
*/
/*
int	store_redirect(t_cmd_list *cmd, t_shell *s)
{
	int	i;

	i = 0;
	while (cmd->cmd[i] != '\0')
	{
		if (cmd->cmd[i] == '>')
			store_write
		if (cmd->cmd[i] == '<')
		
	}
}
*/

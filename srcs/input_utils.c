#include "ft_shell.h"

int	check_colon(char *str, t_shell *s)
{
	int				i;
	int				ret;
	t_split_string	cmds;

	i = 0;
	ret = EXIT_FAILURE;
	if (s->command == NULL && ft_strchr(str, ';')) // is first command;
	{
		cmds = ft_nstrsplit(str, ';');
		while (i++ < cmds.words)
			ret = add_cmd_list(&s->commands, cmds.strings[i]);
		free_tab(cmds.strings, cmds.words);
	}
	return (ret);
}

int	check_pipe(t_cmd_list *list, t_shell *s)
{
	int				i;
	t_split_string	cmd;

	cmd = ft_nstrsplit(line, '|');
	while (i < commands.words)
	{
		if (!(s.cmd.words)
			s->commands = create_node(command.string[i])
		s->commands->pipes = add_node(commands.strings[i]};
		i++;
	}
	check_redirect(c);
}

int	check_redirect(char *cmd, t_shell *s)
{
/*
	{
	command_redirect = nstrsplit(line, '');
	}
	if (strcmp)
	else if (commands = ft_nstrsplit(line, '>'))
	{
	}
*/
}

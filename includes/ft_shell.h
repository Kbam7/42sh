/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 12:14:15 by marvin            #+#    #+#             */
/*   Updated: 2016/08/06 15:03:34 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "libft.h"
# include "builtin.h"

# include <sys/wait.h>

#include <stdio.h> // debug

/*
**	Max pathname and filename macros
*/
# define MAXNAME		255
# define MAXPATH		4096

//	Just a cool DEFINE i found, could be useful
//# define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

/*
**	Macros for errors
*/
# define EXIT_SH				1000
# define ERR_INVALID_ARG		1001
# define ERR_NOTFOUND			1002
# define ERR_CHDIR				1003
# define ERR_EXEC_SHELL			1004
# define ERR_MAX_PATHLEN		1005
# define ERR_NO_FILE			1006
# define ERR_NO_READ			1007
# define ERR_NO_WRITE			1008
# define ERR_NO_EXEC			1009
# define ERR_FORK_FAILED		1010
# define ERR_INVALID_PIPE		1011
# define ERR_CREATE_PIPE		1012
# define ERR_GNL				1013
# define ERR_MALLOC				1014


typedef struct			s_cmd_list
{
	char 				*cmd;
	struct s_cmd_list	*next;
}				t_cmd_list;

typedef struct			s_shell
{
	char		**env_var;	// copy to child
	// init the rest everytime
	char		**shell_var;// do not copy to child
	t_func_opt	func_opt;
	char		**argv;
	char		**paths;
	char		*cwd;
	char		*prompt;
	char		**input;
	int			arg_p;
	int			arg_u;
	t_cmd_list	*commands;
	t_redirs	redir;
	t_pipes		pipe;
//
}				t_shell;

/*
**	shell.c
*/
void			shell_loop(t_shell *s);
int				run_shell(t_shell *s);
void			free_t_shell(t_shell *s);

/*
**	init.c
*/
void			init_env(t_shell *s, int argc, char **argv, char **envp);

/*
**	prompt.c
*/
void			intro_message();
void			set_prompt(t_shell *s);

/*
**	input.c
*/
int				process_input(char *cmd, t_shell *s);
int				process_pipes(char *cmd, t_shell *s);
int				process_redir(char *cmd, t_shell *s);

/*
**	input_utils.c
*/
int				get_commands(t_shell *s);
void			get_input(char *cmd, t_shell *s);
int				store_commands(char *str, t_shell *s);

/*
**	shell_args.c
*/
void			get_arg(int ac, char **argv, t_shell *s);

/*
**	environ.c
*/
char			*ft_getenv(char *name, t_shell *s);
char			*check_env_variables(char *name, t_shell *s);
char			*check_shell_variables(char *name, t_shell *s);

/*
**	execute.c
*/
int				execute_cmd(t_shell *s);
int				try_builtin(t_shell *s);
int				try_system(t_shell *s);

/*
**	tab_funcs.c
*/
char			**ft_tabdup(char **tab, int len);
int				ft_tablen(char **envp);
void			free_tab(void **tab, int len);
char			**tab_trim(char **tab, int len);

/*
**	utils.c
*/
int				check_rights(char *path, int r, int w, int x);
char			***check_env_type(int type, t_shell *s);
void			print_variables(char **env);

/*
**	err.c
*/
int				err(int errno, char *msg);

/*
**	t_cmd_list.c
*/
int				add_cmd(t_cmd_list **cmd_list, char *cmd);
void			free_cmd_list(t_cmd_list **list);
void			print_cmd_list(t_cmd_list *list); // debug


#endif

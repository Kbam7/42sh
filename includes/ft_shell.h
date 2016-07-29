/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 12:14:15 by marvin            #+#    #+#             */
/*   Updated: 2016/07/29 14:59:02 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Helloo

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "libft.h"
# include <sys/wait.h>

/*
**	Max pathname and filename macros
*/
# define MAXNAME		255
# define MAXPATH		4096

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

typedef struct		s_env_func
{
	int	u;	// unsets variable for environment (s->env_var)
	int	i;	// ignores envrironment. temporarily creates an empty environment.
}				t_env_func;

typedef struct			s_echo_func
{
	int	e;		// enable interpretation of backlash escapes
	int	up_e;	// (default) Disable interpretation of backslash escapes
	int	n;		// do  not output trailing newline
}				t_echo_func;

typedef struct			s_cd_func
{
	int	l;	// force symbolic links to be followed
	int	p;	// (default)use the physical directory structure without following symbolic links
}				t_cd_func;

typedef struct			s_func_opt
{
	t_env_func	env;
	t_echo_func	echo;
	t_cd_func	cd;
}				t_func_opt;

typedef struct			s_shell
{
	char		**env_var;	// copy to child
	char		**shell_var;// do not copy to child
	// init the rest everytime
	t_func_opt	func_opt;
	char		**argv;
	char		**paths;
	char		*cwd;
	char		*prompt;
	char		**input;
	int			arg_p;
	int			arg_u;
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
//void			intro_message();
void			set_prompt(t_shell *s);

/*
**	input.c
*/
int				get_input(t_shell *s);

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
int			try_system(t_shell *s);

/*
**	tab_funcs.c
*/
char			**ft_tabdup(char **tab, int len);
int				ft_tablen(char **envp);
void			free_tab(char **tab, int len);

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
**	ft_nstrjoin.c
*/
char			*ft_nstrjoin(char *s1, char *s2, char *s3);

/*
**	###=----[ BUILTIN FUNCTIONS ]-----=###
*/

/*
**	ft_cd.c
*/
int				ft_cd(char **args, t_shell *s);

/*
**	ft_echo.c
*/
int				ft_echo(char **args, t_shell *s);

/*
**	ft_env.c
*/
int				ft_env(char **input, t_shell *s);

/*
**	ft_setenv.c
*/
int				ft_set(int env_type, char *name, char *val, t_shell *s);

/*
**	ft_unsetenv.c
*/
int				ft_unsetenv(char *name, t_shell *s);

#endif

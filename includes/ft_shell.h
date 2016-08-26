/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 12:14:15 by marvin            #+#    #+#             */
/*   Updated: 2016/08/27 00:18:45 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>

# define _GNU_SOURCE		// for O_TMPFILE in heredocs

	#include <stdio.h> // debug


/*
** --[ DEFINES -- FILE/DIRECTORY ]--
*/

# define MAXNAME		255
# define MAXPATH		4096

/*
** --[ DEFINES -- ERRORS ]--
*/

# define EXIT_SH				1000
# define ERR_INVALID_ARG		1001
# define ERR_NOTFOUND			1002
# define ERR_CHDIR				1003
# define ERR_EXEC_SHELL			1004
# define ERR_MAX_PATHLEN		1005
# define ERR_CREATE				1006
# define ERR_NO_FILE			1007
# define ERR_NO_READ			1008
# define ERR_NO_WRITE			1009
# define ERR_NO_EXEC			1010
# define ERR_FORK_FAILED		1011
# define ERR_INVALID_PIPE		1012
# define ERR_CREATE_PIPE		1013
# define ERR_GNL				1014
# define ERR_MALLOC				1015
# define ERR_BAD_TOKEN			1016
# define ERR_BADFD				1017



/*
** --[ STRUCTS -- BUILTIN FUNCTIONS ]--
**
** Builtin function prototypes are at the bottom
**
*/

typedef struct	s_env_func
{
	int	u;	// unsets variable for environment (s->env_var)
	int	i;	// ignores envrironment. temporarily creates an empty environment.
}				t_env_func;

typedef struct	s_echo_func
{
	int	e;		// enable interpretation of backlash escapes
	int	up_e;	// (default) Disable interpretation of backslash escapes
	int	n;		// do  not output trailing newline
}				t_echo_func;

typedef struct	s_cd_func
{
	int	l;	// force symbolic links to be followed
	int	p;	// (default)use the physical directory structure without following symbolic links
}				t_cd_func;

typedef struct	s_func_opt
{
	t_env_func	env;
	t_echo_func	echo;
	t_cd_func	cd;
}				t_func_opt;

/*
** --[ STRUCTS -- PIPES & REDIRS ]--
*/

typedef struct			s_redirs
{
	char			**cmd;		// holds each command/path
	char			*nxt_cmd;	// holds left over chars from after the redir string
	char			**rdr;		// for redir operator strings
//	int				**pipe;		// for redir pipes
	t_split_string	sp;			// redir string split by spaces
	int				sp_i;		// index of current string in sp
	int				dir;
	int				appnd;		// append or not?
	int				n_rdr;
	int				rdr_i;		// current redir index
	// These are for the redirect fd's defined next to the '<'|'>'
	int				pre_fd;			// defines fd on left of operator (<,>)
	int				post_fd;		// defines fd on right of operator (<,>).
}						t_redirs;

typedef struct			s_pipes
{
	int				**pipes;
	int				n_pipes;
	int				pipe_i;
}						t_pipes;

/*
** --[ STRUCTS -- SHELL ]--
*/

typedef struct	s_cmd_list
{
	char				*cmd;
	struct s_cmd_list	*next;
}				t_cmd_list;

typedef struct	s_shell
{
	char		**env_var;	// copy to child shell
	char		**shell_var;// do not copy to child shell
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
// Line editing
    int             cols;
	int				curs_col;
	int				curs_pos;
    int             hight;
	int				h_index;
	int				h_pos;
	int				nbr_space;
	int				on;
	int				str_len;
    int             width;
	char			**env;
	char			**history;
    char            **path;
    char            *home_path;
	char			*new_line;
    char            *oldpwd;
    char            *pwd;
	char			*term_type;
    char            *user;
	struct termios	new_term;
	struct termios	default_term;
	struct termios	old_term;
}				t_shell;

/*
** --[ FUNCTION PROTOTYPES -- LINE EDITING]--
*/

char    **ft_strdup_2(char **src);


void					ft_backspace(t_shell *shell, char *buff);
void					buffer(t_shell *shell);
int						ft_curs_pos(t_shell *shell);
void					ft_clear_screen();
void					ft_curs_col(t_shell *shell);
void					ft_enter(char *buff, t_shell *shell);
void					ft_end_left(t_shell *shell, char *buff);
void					ft_end_right(t_shell *shell, char *buff);
void					ft_history_up(t_shell *shell, char *buff);
void					ft_history_down(t_shell *shell, char *buff);
void					ft_insert(t_shell *shell, char buff);
void					ft_left_word(t_shell *shell, char *buff);
void					ft_line_back_space(t_shell *shell);
void					ft_move_down(t_shell *shell, char *buff);
void					ft_move_up(t_shell *shell, char *buff);
void					ft_move_cur(char *buff, t_shell *shell);
void					ft_move_right(t_shell *shell, char *buff);
void					ft_move_left(t_shell *shell, char *buff);
void					ft_nbr_cols(t_shell *shell);
void					ft_new_history(t_shell *shell);
void                    ft_put_string(t_shell *shell);
void                    ft_put_curs(t_shell *shell);
int						ft_putchar_re(int c);
void					ft_print_char(char *buff, t_shell *shell);
void					ft_right_word(t_shell *shell, char *buff);
char					**ft_semi(t_shell *shell);
int						init_terminal_data (t_shell *shell, char **env);
void					ft_ctrl_l(char *buff);

/*
** --[ FUNCTION PROTOTYPES ]--
*/
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
//void			intro_message(t_shell *s);
void			set_prompt(t_shell *s);

/*
**	input.c
*/
int				process_input(char *cmd, t_shell *s);
int				process_pipes(char *cmd, t_shell *s);

/*
**	commands.c
*/
int				get_commands(t_shell *s);
void			get_input(char *cmd, t_shell *s);
int				store_commands(char *str, t_shell *s);

/*
**	pipes.c
*/
int				process_pipes(char *cmd, t_shell *s);

/*
**	redirs.c
*/
int				process_redir(char *cmd, t_shell *s);

/*
**	analyze_redir.c
*/
int				get_pos(char *str, char ch);
char			*analyze_redir(char **str, char dir, char **cmd, t_shell *s);

/*
**	check_prefix.c
*/
char			*check_prefix(char **str, int pos, char **cmd, t_shell *s);

/*
**	check_postfix.c
*/
char			*check_postfix(char **str, int pos, t_shell *s);

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
//int				try_builtin(t_shell *s);
//int				try_system(t_shell *s);

/*
**	execute_pipe.c
*/
void			child_pipe(t_shell *s);
void			parent_pipe(t_shell *s);

/*
**	execute_input_redir.c
*/
int				child_input_redir(char *str, t_shell *s);

/*
**	execute_output_redir.c
*/
int				child_output_redir(char *str, t_shell *s);
int				parent_output_redir(char *str, t_shell *s);

/*
**	tab_funcs.c
*/
char			**ft_tabdup(char **table, int len);
int				ft_tablen(char **envp);
void			free_tab(void ***table, int len);
char			**tab_trim(char **table, int len);

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
** --[ FUNCTION PROTOTYPES -- TYPEDEFS ]--
*/
/*
**	t_cmd_list.c
*/
int				add_cmd(t_cmd_list **cmd_list, char *cmd);
void			free_cmd_list(t_cmd_list **list);
void			print_cmd_list(t_cmd_list *list); // debug

/*
**	t_redirs.c
*/
int				add_redir(char **rdr_str, char **cmd, t_shell *s);

/*
**	--[ BUILTIN FUNCTIONS ]--
*/
/*
**	ft_cd.c
*/
int				ft_cd(char **args, t_shell *s);
int				change_to_home_dir(t_shell *s);
int				change_to_oldpwd(t_shell *s);
int				cd_change_to_fullpath(char *input, t_shell *s);

/*
**	ft_cd_utils.c
*/
int				cd_invalid_input(char *input);
void			cd_set_arg(char c, t_shell *s);

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

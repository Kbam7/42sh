/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 12:14:15 by marvin            #+#    #+#             */
/*   Updated: 2016/09/11 12:23:16 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "libft.h"
# include <time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# include <dirent.h>
# include <stdio.h>
# include <signal.h>

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
	char			**child_pid;
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
	char		**env_var;
	char		**shell_var;
	t_func_opt	func_opt;
	char		**argv;
	char		**paths;
	char		*cwd;
	char		*prompt;
	int			prompt_len;
	char		**input;
	char		*hdoc_newstr;
	int			hdoc_strlen;
	int			arg_p;
	int			arg_u;
	t_cmd_list	*commands;
	t_redirs	redir;
	t_pipes		pipe;
// Line editing
    char            *cpy_cut;
	int				cpy_nbr;
	int				a;
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
	char			**history;
    char            **path;
	char			*new_line;
    char            *oldpwd;
    char            *pwd;
	char			*term_type;
	struct termios	new_term;
	struct termios	default_term;
	struct termios	old_term;
// rich section
	char	*curr;
	int		cmd_len;
	int		cmd_fork;
	char	**tab_options;
	int		opt_i;
	int		tab_count;
	char	*cd_path;
	char	*file_path;
	char	*word;
// Inhibitors
	char			*wait_str;
	int				wait_strlen;
//signals
	int				fork_pid;
}				t_shell;

/*
** --[ FUNCTION PROTOTYPES -- SIGNALS]--
*/
	void		ft_signals(void);
	void		ft_signal_quit(void);
	void		ft_signal_pause(void);
	void		ft_signal_suspend(void);
	void		ft_signal_segv(void);
	void		ft_signal_int(void);
	void		ft_key_exit(char *buff, t_shell *s);

/*
** --[ FUNCTION PROTOTYPES -- GET-STATIC-SHELL]--
*/
	t_shell 		*ft_get_shell(void);

/*
** --[ FUNCTION PROTOTYPES -- INHIBITORS]--
*/

	void			ft_wait(int trigger, t_shell *s);
	void			ft_check_wait(t_shell *s);
	int				ft_check_inhibitors(char *str);

/*
** --[ FUNCTION PROTOTYPES -- AUTO-COMPLETE]--
*/

void			ft_autocomplete(t_shell *s, char *buff);
void			ft_print_options(t_shell *s);
void			ft_checkcurr(t_shell *s);
int				ft_save_tab_options(t_shell *s, char *d_name);
void			ft_sortoptions(t_shell *s);
void			ft_complete_word(t_shell *s);
int				ft_select_cmd(t_shell *s);
int				ft_select_path(t_shell *s);
void			ft_print_word(t_shell *s);


/*
** --[ FUNCTION PROTOTYPES -- LINE EDITING]--
*/
void					ft_cpy(t_shell *s, char *buff);
void                    ft_cut(t_shell *s, char *buff);
void					ft_paste(t_shell *s, char *buff);
void    				ft_high_right(t_shell *s, char *buff);
void    				ft_high_left(t_shell *s, char *buff);
char					**ft_strdup_2(char **src);
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
int						init_terminal_data (t_shell *shell);
void					ft_ctrl_l(char *buff, t_shell *s);
void					ft_prompt_new(char *new_prompt, t_shell *s);
void					ft_prompt_print(t_shell *s);

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
**	logical_or.c
*/
int				process_logical_or(char *cmd, t_shell *s);

/*
**	logical_and.c
*/
int				process_logical_and(char *cmd, t_shell *s);

/*
**	pipes.c
*/
int				process_pipes(char *cmd, t_shell *s);

/*
**	pipes_wait.c
*/
int				wait_for_children(char **cmds, t_shell *s);
int				ft_wait_child_pipe(int wait, char **cmds, int *curr,
																t_shell *s);

/*
**	pid_array.c
*/
int				add_child_pid(pid_t pid, t_shell *s);
int				remove_child_pid(pid_t pid, t_shell *s);
int				get_child_pid_index(pid_t pid, t_shell *s);

/*
**	redirs.c
*/
int				process_redir(char *cmd, t_shell *s);

/*
**	redirs_utils.c
*/
int				get_string_words(char *str, t_shell *s);
void			redirs_reset_and_free_vars(t_shell *s);

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
int				ft_execute(t_shell *s);

/*
**	execute_builtin.c
*/
int				try_parent_builtin(t_shell *s);
int				try_child_builtin(t_shell *s);

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
**	heredocs.c
*/
int				ft_heredocs(t_shell *s);

/*
**	heredocs_utils.c
*/
void			ft_herestr_write(char *str);
void			ft_heredoc_write(int fd, char *end, t_shell *s);

/*
**	execute_output_redir.c
*/
int				child_output_redir(char *str, t_shell *s);
int				parent_output_redir(char *str, t_shell *s);

/*
**	tab_funcs.c
*/
char			**ft_tabnew(char *str, size_t len);
char			**ft_tabdup(char **table, int len);
int				ft_tablen(char **envp);
void			free_tab(void ***table, int len);
char			**tab_trim(char **table, int len);

/*
**	utils.c
*/
int				ft_sleep(int sec, int nsec);
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
char			*ft_echo_scan(char **args, t_shell *s);
void			ft_echo_string(char **new_str, char *arg, int *triggerer,  int *flag);
int				ft_echo_esc(char **new_str, char *arg, int pos, int trigger);
int				ft_echo_esc_char(char **new_str, int esc_char);
int				ft_echo_skip(char *str);
int				ft_echo_isflag(char *arg, int *flag, int *new_line);
void			ft_echo_env(char **new_str, char *str, int *flag, t_shell *s);
void			ft_echo_clean(char *new_str);
void			ft_echo_addstr(char **str, char c);


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

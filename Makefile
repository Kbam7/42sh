PROG		= 42sh
FLAGS		= -Wall -Wextra -Werror -g
LIBFT		= -L libft -lft -ltermcap
INCLUDES	= -I includes -I libft/includes

SRCS		=	srcs/main.c								\
				srcs/shell.c							\
				srcs/get_shell.c						\
				srcs/init.c								\
				srcs/prompt.c							\
				srcs/input.c							\
				srcs/commands.c							\
				srcs/operators/logical_or.c				\
				srcs/operators/logical_and.c			\
				srcs/operators/pipes.c					\
				srcs/operators/pipes_wait.c				\
				srcs/operators/pid_array.c				\
				srcs/operators/redirs/redirs.c			\
				srcs/operators/heredocs/heredocs.c		\
				srcs/operators/heredocs/heredocs_utils.c\
				srcs/operators/redirs/analyze_redir.c	\
				srcs/operators/redirs/check_prefix.c	\
				srcs/operators/redirs/check_postfix.c	\
				srcs/shell_args.c						\
				srcs/environ.c							\
				srcs/execute/execute.c					\
				srcs/execute/execute_builtin.c			\
				srcs/execute/execute_pipe.c				\
				srcs/execute/execute_output_redir.c		\
				srcs/execute/execute_input_redir.c		\
				srcs/tab_funcs.c						\
				srcs/utils.c							\
				srcs/err.c								\
				srcs/t_redirs.c							\
				srcs/t_cmd_list.c						\
				srcs/line_editing/ft_back_space.c		\
				srcs/line_editing/ft_history.c			\
				srcs/line_editing/ft_keys1.c			\
				srcs/line_editing/ft_keys2.c			\
				srcs/line_editing/ft_keys3.c 			\
				srcs/line_editing/ft_keys4.c			\
				srcs/line_editing/ft_print_char.c		\
				srcs/line_editing/ft_init_terminal.c	\
				srcs/line_editing/ft_strdup_2.c			\
				srcs/line_editing/ft_prompt.c			\
				srcs/line_editing/ft_cpy.c				\
				srcs/line_editing/ft_cut.c				\
				srcs/line_editing/ft_highlight.c		\
				srcs/autocomplete/ft_autocomplete.c		\
				srcs/autocomplete/autocomplete_path.c	\
				srcs/autocomplete/autocomplete_utils.c	\
				srcs/autocomplete/print_options.c		\
				srcs/inhibitors/ft_check_wait.c			\
				srcs/inhibitors/ft_wait.c				\
				srcs/inhibitors/ft_check_inhibitors.c	\
				srcs/signals/ft_signals.c				\
				srcs/signals/ft_signal_quit.c			\
				srcs/signals/ft_signal_suspend.c		\
				srcs/signals/ft_signal_segv.c			\
				srcs/signals/ft_signal_int.c			\

BUILTIN		=	srcs/builtin/ft_cd.c 					\
				srcs/builtin/ft_cd_utils.c				\
				srcs/builtin/ft_env.c					\
				srcs/builtin/ft_echo.c					\
				srcs/builtin/ft_echo_addstr.c			\
				srcs/builtin/ft_echo_clean.c			\
				srcs/builtin/ft_echo_env.c				\
				srcs/builtin/ft_echo_esc.c				\
				srcs/builtin/ft_echo_esc_char.c			\
				srcs/builtin/ft_echo_isflag.c			\
				srcs/builtin/ft_echo_scan.c				\
				srcs/builtin/ft_echo_skip.c				\
				srcs/builtin/ft_echo_string.c			\
				srcs/builtin/ft_setenv.c				\
				srcs/builtin/ft_unsetenv.c

all: $(PROG)

$(PROG):
	@make -s -C libft all
	@gcc $(FLAGS) $(INCLUDES) $(SRCS) $(BUILTIN) $(LIBFT) -o $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mMade '$(PROG)'\033[0m"

clean:
	@make -s -C libft clean

fclean: clean
	@make -s -C libft fclean
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mRemoved '$(PROG)'\033[0m"

re: fclean all

run:
	@rm -f $(PROG)
	@echo "\033[01;36m$(PROG) -- \033[00;32mRemoved '$(PROG)'\033[0m"
	@$(MAKE) -s all

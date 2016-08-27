PROG		= 42sh
FLAGS		= -Wall -g
LIBFT		= -L libft -lft -ltermcap
INCLUDES	= -I includes -I libft/includes

SRCS		=	srcs/main.c						\
				srcs/shell.c					\
				srcs/init.c						\
				srcs/prompt.c					\
				srcs/input.c					\
				srcs/commands.c					\
				srcs/pipes.c					\
				srcs/pipetab_funcs.c			\
				srcs/redirs/redirs.c			\
				srcs/redirs/analyze_redir.c		\
				srcs/redirs/check_prefix.c		\
				srcs/redirs/check_postfix.c		\
				srcs/shell_args.c				\
				srcs/environ.c					\
				srcs/execute.c					\
				srcs/execute_pipe.c				\
				srcs/execute_output_redir.c		\
				srcs/execute_input_redir.c		\
				srcs/tab_funcs.c				\
				srcs/utils.c					\
				srcs/err.c						\
				srcs/t_redirs.c					\
				srcs/t_cmd_list.c				\
				srcs/line_editing/ft_keys3.c 			\
				srcs/line_editing/ft_back_space.c		\
				srcs/line_editing/ft_history.c			\
				srcs/line_editing/ft_keys2.c			\
				srcs/line_editing/ft_keys1.c			\
				srcs/line_editing/ft_print_char.c		\
				srcs/line_editing/ft_init_terminal.c	\
				srcs/line_editing/ft_strdup_2.c			\
				srcs/autocomplete/ft_autocomplete.c		\
				srcs/autocomplete/autocomplete_path.c	\
				srcs/autocomplete/autocomplete_utils.c	\

BUILTIN		=	srcs/builtin/ft_cd.c			\
				srcs/builtin/ft_cd_utils.c		\
				srcs/builtin/ft_echo.c			\
				srcs/builtin/ft_env.c			\
				srcs/builtin/ft_setenv.c		\
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

PROG		= 21sh
FLAGS		= -Wall -Wextra -Werror -g
LIBFT		= -L libft -lft
INCLUDES	= -I includes -I libft/includes

SRCS		=	srcs/main.c				\
				srcs/shell.c			\
				srcs/init.c				\
				srcs/prompt.c			\
				srcs/input.c			\
				srcs/shell_args.c		\
				srcs/environ.c			\
				srcs/execute.c			\
				srcs/tab_funcs.c			\
				srcs/utils.c			\
				srcs/err.c				\
				srcs/ft_nstrjoin.c

BUILTIN		=	srcs/builtin/ft_cd.c			\
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
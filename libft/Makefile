# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbamping <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/28 14:01:24 by kbamping          #+#    #+#              #
#*   Updated: 2016/08/31 13:10:05 by kgani            ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror -g3

SRCS = srcs/ft_atoi.c srcs/ft_bzero.c srcs/ft_isalnum.c 		\
	srcs/ft_isalpha.c srcs/ft_isascii.c srcs/ft_isdigit.c 		\
	srcs/ft_islower.c srcs/ft_isprint.c srcs/ft_isupper.c 		\
	srcs/ft_itoa_base.c srcs/ft_itoa.c srcs/ft_memalloc.c		\
	srcs/ft_memccpy.c srcs/ft_memchr.c srcs/ft_memcmp.c 		\
	srcs/ft_memcpy.c srcs/ft_memdel.c srcs/ft_memmove.c 		\
	srcs/ft_memset.c srcs/ft_putchar.c srcs/ft_putchar_fd.c 	\
	srcs/ft_putendl.c srcs/ft_putendl_fd.c srcs/ft_putnbr.c 	\
	srcs/ft_putnbr_fd.c srcs/ft_putstr.c srcs/ft_putstr_fd.c 	\
	srcs/ft_strcat.c srcs/ft_strchr.c srcs/ft_strclr.c 			\
	srcs/ft_strcmp.c srcs/ft_strcpy.c srcs/ft_strdel.c 			\
	srcs/ft_strdup.c srcs/ft_strequ.c srcs/ft_striter.c 		\
	srcs/ft_striteri.c srcs/ft_strjoin.c srcs/ft_strlcat.c 		\
	srcs/ft_strlen.c srcs/ft_strmap.c srcs/ft_strmapi.c 		\
	srcs/ft_strncat.c srcs/ft_strncmp.c srcs/ft_strncpy.c 		\
	srcs/ft_strnequ.c srcs/ft_strnew.c srcs/ft_strnjoin.c		\
	srcs/ft_strnstr.c srcs/ft_strrchr.c srcs/ft_strrev.c 		\
	srcs/ft_strsplit.c srcs/ft_strstr.c srcs/ft_strsub.c 		\
	srcs/ft_strtrim.c srcs/ft_tolower.c srcs/ft_toupper.c 		\
	srcs/ft_uitoa.c srcs/ft_uitoa_base.c srcs/ft_ctostr.c 		\
	srcs/ft_gnl.c srcs/ft_lstadd.c srcs/ft_lstclear.c 			\
	srcs/ft_lstdel.c srcs/ft_lstdelone.c srcs/ft_lstiter.c		\
	srcs/ft_lstlen.c srcs/ft_lstmap.c srcs/ft_lstnclear.c		\
	srcs/ft_lstnew.c srcs/ft_lstpushback.c srcs/ft_lstrev.c 	\
	srcs/ft_printf.c srcs/ft_strchr_end.c srcs/ft_swap.c  		\
	srcs/ft_float_swap.c srcs/ft_strtoupper.c srcs/ft_nstrsplit.c	\
	srcs/ft_memswap.c srcs/ft_isint.c srcs/ft_sprintf.c			\
	srcs/ft_fprintf.c srcs/ft_strjoinstr.c srcs/ft_iswhtspc.c	\
	srcs/ft_nstrsplitstr.c srcs/ft_strcaps.c srcs/ft_countarray.c \
	srcs/ft_strcap.c srcs/ft_free_split.c

OBJS = ft_atoi.o ft_bzero.o ft_isalnum.o ft_strcap.o		\
	ft_isalpha.o ft_isascii.o ft_isdigit.o 					\
	ft_islower.o ft_isprint.o ft_isupper.o 					\
	ft_itoa_base.o ft_itoa.o ft_memalloc.o 					\
	ft_memccpy.o ft_memchr.o ft_memcmp.o 					\
	ft_memcpy.o ft_memdel.o ft_memmove.o 					\
	ft_memset.o ft_putchar.o ft_putchar_fd.o 				\
	ft_putendl.o ft_putendl_fd.o ft_putnbr.o 				\
	ft_putnbr_fd.o ft_putstr.o ft_putstr_fd.o 				\
	ft_strcat.o ft_strchr.o ft_strclr.o 					\
	ft_strcmp.o ft_strcpy.o ft_strdel.o 					\
	ft_strdup.o ft_strequ.o ft_striter.o 					\
	ft_striteri.o ft_strjoin.o ft_strlcat.o 				\
	ft_strlen.o ft_strmap.o ft_strmapi.o 					\
	ft_strncat.o ft_strncmp.o ft_strncpy.o 					\
	ft_strnequ.o ft_strnew.o ft_strnjoin.o 					\
	ft_strnstr.o ft_strrchr.o ft_strrev.o 					\
	ft_strsplit.o ft_strstr.o ft_strsub.o 					\
	ft_strtrim.o ft_tolower.o ft_toupper.o 					\
	ft_uitoa.o ft_uitoa_base.o ft_ctostr.o 					\
	ft_gnl.o ft_lstadd.o ft_lstclear.o 						\
	ft_lstdel.o ft_lstdelone.o ft_lstiter.o 				\
	ft_lstlen.o ft_lstmap.o ft_lstnclear.o 					\
	ft_lstnew.o ft_lstpushback.o ft_lstrev.o 				\
	ft_printf.o ft_strchr_end.o ft_swap.o ft_float_swap.o 	\
	ft_strtoupper.o ft_nstrsplit.o ft_memswap.o ft_isint.o	\
	ft_sprintf.o ft_fprintf.o ft_strjoinstr.o ft_iswhtspc.o	\
	ft_nstrsplitstr.o ft_strcaps.o ft_countarray.o			\
	ft_free_split.o

all: $(NAME)

$(NAME):
	@echo "\033[01;33mlibft -- \033[00;32mCompiling files...\033[0m"
	@gcc $(FLAGS) -c $(SRCS) -I includes
	@echo "\033[01;33mlibft -- \033[00;32mMaking archive...\033[0m"
	@ar rc libft.a $(OBJS)
	@ranlib $(NAME)
	@echo "\033[01;33mlibft -- \033[00;32mMaking 'objs' directory...\033[0m"
	@mkdir -p objs
	@mv $(OBJS) objs/
	@echo "\033[01;33mlibft -- \033[00;32m obj files moved to 'objs' dir...\033[0m"

clean:
	@rm -rf objs/
	@echo "\033[01;33mlibft -- \033[00;32mRemoved 'objs' directory...\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[01;33mlibft -- \033[00;32mRemoved '$(NAME)' archive...\033[0m"

re: fclean all

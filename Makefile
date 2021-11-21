# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 13:06:02 by mouassit          #+#    #+#              #
#    Updated: 2021/11/20 10:07:49 by ayafdel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC =./srcs/main.c \
	  ./srcs/parsing/parsing.c \
	  ./srcs/parsing/linkedlist.c \
	  ./srcs/execution/ft_exit_bi.c \
	  ./srcs/execution/free_struct.c \
	  ./srcs/execution/ft_unset.c \
	  ./srcs/execution/ft_echo.c \
	  ./srcs/execution/ft_pwd.c \
	  ./srcs/execution/ft_cd.c \
	  ./srcs/execution/ft_export.c \
	  ./srcs/execution/ft_env.c \


LIBFT = ./libraries/libft/libft.a

all : $(NAME)

$(NAME):
	@make -s -C ./libraries/libft
	@gcc -Wall -Wextra -Werror -lreadline -fsanitize=address -g -I .  $(SRC) $(LIBFT) -D BUFFER_SIZE=1 -o $(NAME)


clean:
	@make -s -C ./libraries/libft clean

fclean: clean
	@make -s -C ./libraries/libft fclean
	@rm -rf $(NAME)

re: fclean all
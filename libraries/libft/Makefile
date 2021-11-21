# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 15:42:34 by ayafdel           #+#    #+#              #
#    Updated: 2021/11/06 15:52:23 by ayafdel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCO = ft_strcmp.c ft_strdup_null.c ft_indexof.c ft_error.c ft_free_first.c print_strings.c ft_strjoin_char.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strncmp.c ft_strdup.c ft_memmove.c
all : $(NAME)
$(NAME) :
	    gcc $(FLAGS) -c $(SRCO)
		    ar rc $(NAME) *.o
clean :
	    rm -rf *.o
fclean : clean
	    rm -rf $(NAME)
re : fclean all
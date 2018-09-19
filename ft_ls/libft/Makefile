# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szama <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/22 12:31:51 by szama             #+#    #+#              #
#    Updated: 2017/09/11 16:01:55 by szama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -I includes

SRC = ft_strlen.c ft_strcmp.c ft_memset.c\
	  ft_memcpy.c ft_strjoin.c ft_strnew.c \
	  ft_putchar.c ft_putstr.c ft_putendl.c \
	  ft_putnbr.c ft_itoa.c ft_int_len.c \


OBJ = ft_strlen.o ft_strcmp.o ft_memset.o\
	  ft_memcpy.o ft_strjoin.o ft_strnew.o \
	  ft_putchar.o ft_putstr.o ft_putendl.o \
	  ft_putnbr.o ft_itoa.o ft_int_len.o \

all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

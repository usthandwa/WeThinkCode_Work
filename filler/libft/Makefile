# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szama <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/22 12:31:51 by szama             #+#    #+#              #
#    Updated: 2017/09/11 15:48:57 by szama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -I includes -c

HEADER = includes/libft.h

SRC1 = ft_strlen.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_strcpy.c \
	   ft_strncpy.c ft_strdup.c ft_strcat.c ft_strstr.c ft_strchr.c \
	   ft_strrchr.c ft_strnstr.c ft_strncat.c ft_strlcat.c \
	   ft_tolower.c ft_toupper.c ft_memset.c ft_memcpy.c ft_memccpy.c \

SRC2 = ft_memmove.c ft_memchr.c ft_memcmp.c ft_bzero.c ft_isprint.c \
	   ft_isascii.c ft_isalnum.c ft_isdigit.c ft_isalpha.c \
	   ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_strclr.c \
	   ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strequ.c \

SRC3 = ft_strnequ.c ft_strjoin.c ft_putchar_fd.c ft_putstr_fd.c \
	   ft_putendl_fd.c ft_strrev.c ft_int_len.c ft_striter.c \
	   ft_striteri.c ft_strmap.c ft_strmapi.c ft_strsub.c ft_strtrim.c \
	   ft_itoa.c ft_abs.c ft_putnbr_fd.c ft_strsplit.c ft_strlen_2d.c\

SRC4 = ft_freearray.c ft_split.c ft_startwith.c ft_countwordsall.c get_next_line.c\
	   ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
	   ft_lstlen.c ft_int_len.c ft_swap.c\

SRC = $(SRC1) $(SRC2) $(SRC3) $(SRC4)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

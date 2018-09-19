# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szama <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/17 15:54:55 by szama             #+#    #+#              #
#    Updated: 2018/08/17 15:55:00 by szama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = filler
CC = gcc
FLAGS = -Wall -Wextra -Werror
INC = -I ./include

SRC =  piece.c read_map.c sorter.c find_dist.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
		@$(MAKE) -C libft/ all
		@$(CC) $(FLAGS) -L libft/ -lft $(INC) $(SRC) ft_filler.c -o $(NAME)

clean:
	@$(MAKE) -C libft/ clean
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)

re: fclean all
	@$(MAKE) -C libft/ re

.PHONY: all clean fclean re

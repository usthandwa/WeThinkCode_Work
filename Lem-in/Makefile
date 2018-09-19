# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szama <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/05 17:39:31 by szama             #+#    #+#              #
#    Updated: 2018/09/05 17:39:37 by szama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Lem-in

SRC = source/create_stacks.c source/main.c source/links.c source/errors.c \
	  source/help.c\

OBJ = *.o

CFLAGS= gcc -Wall -Wextra -Werror -o

IN5 = /goinfre/szama/Desktop/duplicates/Lem-in/lem/maps/map0

all: $(NAME) $(NAME2)

$(NAME):
	@$(MAKE) -C libft/
	@$(CFLAGS) $(NAME) $(SRC) -L libft/ -lft -I /libft/includes -I includes

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft/ fclean

norm:
	norminette $(SRC)

grind:
	@echo "`valgrind -v --log-fd=1 --track-fds=yes --read-inline-info=yes --read-var-info=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) < $(IN5) > log`"
re: fclean all

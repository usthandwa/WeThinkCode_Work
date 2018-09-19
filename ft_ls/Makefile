# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szama <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/16 11:47:23 by szama             #+#    #+#              #
#    Updated: 2017/09/14 11:35:02 by szama            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c	file_check.c	lslong.c	do_ls.c	

FLAGS = gcc -Wall -Werror -Wextra -o

all : $(NAME)

$(NAME):
	@echo "please wait for $(NAME)..."
	@$(MAKE)  -C libft/
	@$(FLAGS) $(NAME) $(SRC) -L libft/ -lft -I libft/includes -I includes

clean:
	@rm -f $(NAME)

fclean:
	@echo "cleaning $(NAME) files..."
	@$(MAKE) fclean -C libft/
	@rm -f $(NAME)

re : fclean all

norm:
	@norminette $(SRC) ft_ls.h

NAME1 = checker
NAME2 = push_swap

SRC1 = operands.c chksort.c stacks.c push.c validator.c
SRC2 = magic.c num_check.c pushswap.c

OBJ = *.o

CFLAGS= gcc -Wall -Wextra -Werror -o

all: $(NAME1) $(NAME2)

$(NAME1):
	@$(MAKE)  -C libft/ re
	@$(CFLAGS) $(NAME1) $(SRC1) checker.c -L libft/ -lft -I libft/includes -I includes

$(NAME2):
	@$(MAKE)  -C libft/ re
	@$(CFLAGS) $(NAME2) $(SRC1) $(SRC2) -L libft/ -lft -I libft/includes -I includes

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME1) $(NAME2)

IN5 = 176 126 115 49 114 152 193 60 90
norm:
	norminette $(SRC1) checker.c
	norminette $(SRC2)
	@for V in libft/*.c ; do \
        norminette $$V; \
    done

DATE = $(shell date +'%G-%m-%d-%Hh%Mm')
grind:
	@echo "`valgrind -v --log-fd=1 --track-fds=yes --read-inline-info=yes --read-var-info=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME1) $(IN5) >> logC`"
	@echo "`valgrind -v --log-fd=1 --track-fds=yes --read-inline-info=yes --read-var-info=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME2) $(IN5) >> logPs`"
re: fclean all

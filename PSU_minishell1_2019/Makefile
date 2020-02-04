##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile for bistro-matic
##

SRC		=		src/*.c

SRCT 	=		./tests/

NAME	=		mysh

FLAGS	=		-L./lib/my -lmy -I./include/

TFLAG 	= 		-lcriterion --coverage -fprofile-arcs

COV 	=		--exclude tests/ -o coverage.html



all:
		make -C ./lib/my re
		gcc -o $(NAME) $(SRC) $(FLAGS)

clean:
		rm -f $(OBJ)
		make -C ./lib/my clean
		rm -f *.html
		rm -f *.gcno
		rm -f *.gcda

fclean:	clean
		rm -f $(NAME)
		make -C ./lib/my fclean
		rm -f *.gcno
		rm -f *.gcda
		rm -f *.html
		rm -f vgcore.*

clear:
		clear

re: clear fclean all

tests_run:
		make -C ./lib/my re
		gcc -o $(NAME) $(SRC) $(SRCT) $(TFLAG) $(FLAGS)
		-./$(NAME)
		gcovr --exclude tests/
		gcovr --html $(COV) --html-title $(NAME) --html-details
		rm -f *.gcno
		rm -f *.gcda

valgrind: fclean
	clear
	make -C ./lib/my valgrind
	gcc -g -o $(NAME) $(SRC) $(FLAGS)
	valgrind -s --leak-check=full --track-origins=yes ./$(NAME) 2>&1 | cat -e #&> valgrind_log

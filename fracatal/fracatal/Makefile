##
## EPITECH PROJECT, 2023
## fracatal
## File description:
## Makefile
##

SRCS = $(wildcard *.c)

NAME = fractals

all:
	gcc $(SRCS) -o $(NAME)

clean:
	rm -rf *.o *.~ *.#
fclean:	clean
	rm -rf $(NAME)

re:	fclean all
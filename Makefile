##
## VRMELO PROJECT, 2024
## Daxflight
## File description:
## The project Makefile
##

SRCS	=	src/main.c	\
			src/error.c	\
			src/my_strtok.c	\
			src/match1.c


OBJS	= $(SRCS:.c=.o)

BINARY = daxflight

all: $(BINARY)

$(BINARY): $(OBJS)
	gcc -o $(BINARY) $(OBJS) -g3 -Og

unit_tests: fclean $(BINARY)
	gcc -o unit_tests tests/test_minishell.c $(SRCS) -lcriterion --coverage

tests_run: unit_tests
	./unit_tests
	gcovr --exclude tests/ --branches
	gcovr --exclude tests/

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*~" -delete
	find . -type f -name "#*#" -delete
	find . -type f -name "a.out" -delete
	find . -type f -name "vgcore*" -delete
	find . -type f -name "*.gcda" -delete
	find . -type f -name "*.gcno" -delete

fclean: clean
	rm -f $(BINARY) unit_tests

re: fclean all

.PHONY: all clean fclean re
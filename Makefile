NAME = ftls
CC = gcc
SOUS = *.c
HEAD = ./includes

all:
	$(CC) -std=c99 -o $(NAME) $(SOUS) -I $(HEAD) -L ./libft -lft
clean:
	rm $(NAME)

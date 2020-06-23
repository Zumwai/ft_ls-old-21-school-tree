NAME = ftls
CC = gcc
SOUS = *.c
HEAD = ./includes

all:
	$(CC) -o $(NAME) $(SOUS) -I $(HEAD)
clean:
	rm $(NAME)

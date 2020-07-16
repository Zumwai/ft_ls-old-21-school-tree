NAME = ft_ls
COM = gcc
HEAD_FTLS = ./includes/
HEAD_L = ./libft/
HEAD_LIB = libft.h
HEAD_H = ft_ls.h
HEAD_F = $(HEAD_FTLS) \
		$(HEAD_L)
HEADS = $(addprefix -I, $(HEAD_F))
LIB_F = ./libft/
LIB = libft.a
LIB_D = $(addprefix $(LIB_F), $(LIB))
LIB_C = -L $(LIB_F) -lft
SOUS = ./src/
SOUS_FIL = main.c \
		   columns.c \
		   err.c \
		   ft_scope.c \
		   ft_separetion.c \
		   helpers.c \
		   info_list.c \
		   key_t_time.c \
		   key_stlex.c \
		   key_uru.c \
		   misc.c \
		   parse_key.c \
		   printer.c \
		   reader.c	\
		   ft_calc.c
OBJS = $(SOUS_FIL:.c=.o)
SOUS_F = $(addprefix $(SOUS), $(SOUS_FIL))
OBJS_F = $(addprefix $(BIN), $(OBJS))
BIN = ./bin/
TRASH = ft_ls.h.gch \
		ft_ls.dSYM
FLAGS = -Wall -Wextra -Werror
REMOVE = rm -rf

.PHONY: all clean re

all: $(NAME)
$(NAME): $(OBJS_F) $(HEAD_FTLS)$(HEAD_H) $(LIB_D)
	$(COM) $(FLAGS) -o $@ $(OBJS_F) $(HEADS) $(LIB_C)
$(LIB_D): $(LIB_F)
	$(MAKE) -sC $(LIB_F) all
$(BIN)%.o: $(SOUS)%.c
	mkdir -p $(BIN) && \
	$(COM) $(FLAGS) -c $< -o $@ $(HEADS)
clean:
	@$(REMOVE) $(OBJS_F) $(BIN) $(TRASH)
	@make -sC $(LIB_F) clean
fclean: clean
	@$(REMOVE) $(NAME)
	@make -sC $(LIB_F) fclean
re: fclean all

.PHONY: clean fclean re
.SUFFIXES:

CC =		gcc
EXEC =		gnl
LIB =		ft
SRCS_DIR =	./
OBJS_DIR =	./
LIB_DIR = 	./libft/
HEADER =	./
CFLAGS =	-Wall -Werror -Wextra -g
ARFLAGS =	-rcs
CFILES =	main get_next_line

SRCS =		$(CFILES:%=$(SRCS_DIR)%.c)
OBJS =		$(SRCS:%.c=$(OBJS_DIR)%.o)

all:
	make -C libft/
	$(CC) $(SRCS) -I$(HEADER) -L$(LIB_DIR) -l$(LIB) -o $(EXEC) $(CFLAGS)

clean:
	rm -f $(OBJS)
	@make -C libft/ clean
	@echo $@ Done !

fclean:		clean
	rm -f $(EXEC)
	@make -C libft/ fclean
	@echo $@ Done !

re:			fclean all

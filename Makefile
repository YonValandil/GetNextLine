#Regles qui ne concerne pas des noms de fichiers
.PHONY: clean fclean re
#Enleve les directives implicites par defauts
.SUFFIXES:

CC =		gcc
EXEC =		bin
NAME =		ft
SRCS_DIR =	./srcs/
OBJS_DIR =	./
LIB_DIR = 	./libft/
HEADER =	./includes/
CFLAGS =	-Wall -Werror -Wextra
ARFLAGS =	-rcs
CFILES =	main get_next_line

#pattern sub : $(var:pattern=replacement)
SRCS =		$(CFILES:%=$(SRCS_DIR)%.c)
OBJS =		$(SRCS:%.c=$(OBJS_DIR)%.o)

all:
	make -C libft/
	$(CC) $(SRCS) -I$(HEADER) -L$(LIB_DIR) -l$(NAME) -o $(EXEC) $(CFLAGS)
	@echo $(EXEC) Done !
	@echo ------------------
	@./$(EXEC) sample.text

clean:
	rm -f $(OBJS)
	@make -C libft/ clean
	@echo $@ Done !

fclean:		clean
	rm -f $(EXEC)
	@make -C libft/ fclean
	@echo $@ Done !

re:			fclean all

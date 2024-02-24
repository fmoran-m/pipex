NAME = pipex

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = -Wall -Wextra -Werror

INCLUDES = pipex.h

RM = rm -f

SRC = main.c free_functions.c childs.c path.c pipex_utils.c

OBJS = ${SRC:.c=.o}

$(NAME): $(OBJS) $(HEADER)
		@$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) -fsanitize=address $(OBJS) $(LIBFT)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJS)
		@cd $(LIBFTDIR) && make clean

fclean: clean
		@$(RM) $(NAME)
		@cd $(LIBFTDIR) && make fclean

re: fclean all

.PHONY = all clean fclean re bonus

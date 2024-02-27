# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 15:41:45 by fmoran-m          #+#    #+#              #
#    Updated: 2024/02/27 15:42:00 by fmoran-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = -Wall -Wextra -Werror

INCLUDES = pipex.h

RM = rm -f

SRC = main.c exit_functions.c childs.c path.c 

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

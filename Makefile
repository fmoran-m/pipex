# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 15:41:45 by fmoran-m          #+#    #+#              #
#    Updated: 2024/02/28 17:40:39 by fmoran-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = -Wall -Wextra -Werror

INCLUDES = pipex.h

INCLUDES_BONUS = pipex_bonus.h

RM = rm -f

SRC = main.c exit_functions.c childs.c path.c

OBJS = ${SRC:.c=.o}

BONUS = main_bonus.c exit_functions_bonus.c childs_bonus.c path_bonus.c

BONUS_OBJS = ${BONUS:.c=.o}

$(NAME): $(OBJS) $(INCLUDES)
		$(RM) $(BONUS_OBJS)
		@$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS) $(INCLUDE_BONUS)
		$(RM) $(OBJS)
		@$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(BONUS_OBJS) $(LIBFT)

clean:
		@$(RM) $(BONUS_OBJS) $(OBJS)
		@cd $(LIBFTDIR) && make clean

fclean: clean
		@$(RM) $(NAME)
		@cd $(LIBFTDIR) && make fclean

re: fclean all

.PHONY = all clean fclean re bonus

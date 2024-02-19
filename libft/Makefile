NAME = libft.a

FLAGS := -Wall -Wextra -Werror

RM = rm -f

CC = gcc

AR = ar rcs

SRC =	ft_isalpha.c ft_isascii.c ft_isalnum.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memcmp.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c	ft_tolower.c ft_strchr.c ft_strnstr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_striteri.c ft_split.c ft_utoa.c ft_lower_hextoa.c ft_upper_hextoa.c ft_long_hextoa.c ft_printf.c write_characters.c write_numbers.c get_next_line.c free_file.c ft_atoi_base.c ft_strcmp.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

HEADER = libft.h

OBJS = ${SRC:.c=.o} 

O.BONUS = ${BONUS:.c=.o}

all:	$(NAME) 

$(NAME): $(OBJS) $(HEADER)
	$(AR) $(NAME) $(OBJS)

bonus: $(O.BONUS) $(OBJS) $(HEADER)
	$(AR) $(NAME) $(O.BONUS) $(OBJS)

%.o:%.c
		$(CC) $(FLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(O.BONUS)

fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean bonus all

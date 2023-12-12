SRCS	= main.c color.c libft.a
OBJS	= $(SRCS:.c=.o)
NAME	= a.out
CC		= cc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -Iincludes -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

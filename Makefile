SRCS	= main.c color.c load_map.c check.c
OBJS	= $(SRCS:.c=.o)
NAME	= a.out
LIB		= libft.a
CC		= cc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -Iincludes -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

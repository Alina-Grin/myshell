CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = minishell.c

DIR = libft/libft.a

OBJS = $(SRCS:.c=.o)

NAME = minishell

.PHONY: all
all: $(NAME)

$(NAME): $(DIR) $(OBJS)
	$(CC) $(OBJS) libft/libft.a -o $(NAME)

$(DIR):
	# cd libft && $(MAKE)
	make -C libft

%.o: %.c ft_ls.h
	$(CC)  $< -c $(CFLAGS) -o $@

.PHONY: clean
clean:
	@rm -f $(OBJS)
	make -C libft/ clean

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	make -C libft/ fclean

.PHONY: re
re: fclean all

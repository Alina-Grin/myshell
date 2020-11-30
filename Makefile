# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szeftyr <szeftyr@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 11:46:54 by szeftyr           #+#    #+#              #
#    Updated: 2020/11/05 11:46:54 by szeftyr          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = minishell.c parse_input.c path.c signal.c ft_split.c cmd_setting_env.c \
		cmd_env.c cmd_echo.c cmd_cd.c

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

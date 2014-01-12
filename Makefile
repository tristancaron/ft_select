#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/26 11:52:41 by tcaron            #+#    #+#              #
#    Updated: 2013/12/30 21:10:39 by tcaron           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_select

CFLAGS = -pedantic -Wall -Werror -Wextra -O3 -g -Wconversion

FILES = main.c ft_control.c ft_keycatch.c ft_termode.c \
		ft_display.c ft_loop.c ft_esc_input.c \
		ft_get_line.c ft_print.c ft_keycatch_2.c ft_display_2.c \
		ft_display_3.c ft_keycatch_3.c

SRC = $(addprefix src/, $(FILES))

OBJ = $(SRC:src/%.c=obj/%.o)

CC = gcc

.PHONY: all clean fclean re dirobj

.SILENT: dirobj

all: dirobj $(NAME)

$(NAME): $(OBJ)
		make -C ./libft
		$(CC) -L./libft -lft -ltermcap -o $(NAME) $(OBJ)

obj/%.o : src/%.c
		$(CC) $(CFLAGS) -Iinc -I./libft -o $@ -c $^

clean:
	make clean -C ./libft
	rm -rf obj

fclean: clean
		make fclean -C ./libft
		rm -f $(NAME)

re: fclean all

dirobj:
	mkdir -p obj

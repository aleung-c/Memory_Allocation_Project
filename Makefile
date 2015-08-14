# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 13:38:15 by aleung-c          #+#    #+#              #
#    Updated: 2015/08/14 10:53:22 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

INCLUDES = malloc.h

SRC = malloc.c main.c show_alloc_mem.c free.c realloc.c search_mem.c \
		add_seg_to_chunk.c allocate_mem.c show_alloc_mem_display.c

OBJ = $(SRC:.c=.o)

LIB = ./libft/

CC = gcc -g -Wall -Werror -Wextra

all : Lib $(NAME) $(SRC)

$(NAME) : $(SRC)
	$(CC) -o $(NAME) $(SRC) -L./libft/ -lft

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re Lib
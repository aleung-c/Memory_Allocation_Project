# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 13:38:15 by aleung-c          #+#    #+#              #
#    Updated: 2015/06/05 15:15:26 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

INCLUDES = malloc.h

SRC = malloc.c main.c

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
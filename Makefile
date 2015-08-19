# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/04 13:38:15 by aleung-c          #+#    #+#              #
#    Updated: 2015/08/19 18:12:32 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

vpath %.c ./

SRC = malloc.c show_alloc_mem.c free.c realloc.c search_mem.c \
add_seg_to_chunk.c allocate_mem.c show_alloc_mem_display.c \
tools.c

OBJ = $(patsubst %.c, ./%.o, $(SRC))

CFLAGS = -Wall -Werror -Wextra
INCS = -I./

RM = rm -f

all: $(NAME)

.PHONY: all clean fclean re dev

$(NAME): $(OBJ) ./malloc.h
	@$(CC) -shared $(INCS) -o $(NAME) $(OBJ)
	@ln -sf $(NAME) libft_malloc.so

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) libft_malloc.so
	@$(RM) $(NAME)

re: fclean all

./%.o: %.c
	@$(CC) -fpic -c $(CFLAGS) $(INCS) $< -o $@

.PHONY: all clean fclean re
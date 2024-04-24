# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 17:58:54 by mokutucu          #+#    #+#              #
#    Updated: 2024/04/22 18:43:22 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	push_swap

CC		=	cc

CFLAGS  =   -Wall -Wextra -Werror

RM		=	rm -rf

SRC_DIR	=	./src/

OBJ_DIR	=	./objs/

LIB_DIR =	./libs/libft/

SRC		=	main.c

INCLUDE	=	-I $(LIB_DIR)

LIBS    =	-L$(LIB_DIR) -lft

OBJ		=	${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}

all: $(NAME)

$(LIB_DIR)libft.a:
	make -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIB_DIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(LIB_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

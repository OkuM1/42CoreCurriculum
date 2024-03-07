# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 17:08:49 by mokutucu          #+#    #+#              #
#    Updated: 2024/03/07 17:32:51 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
LIB	= src/libft.a

SRC_CLIENT = src/client.c 
SRC_SERVER = src/server.c

OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)
OBJ_SERVER	= $(SRC_SERVER:.c=.o)

RM		= rm -f
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDE = -I include

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
		@make -C src/libft
		$(CC) $(CFLAGS) $(OBJ_CLIENT) $(INCLUDE) $(LIB) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
		@make -C src/libft
		$(CC) $(CFLAGS) $(OBJ_SERVER) $(INCLUDE) $(LIB) -o $(NAME_SERVER)

clean:
		@make clean -C src/libft
		$(RM) $(OBJ_CLIENT)
		$(RM) $(OBJ_SERVER)

fclean: clean
		@make clean -C src/libft
		$(RM) $(NAME_CLIENT)
		$(RM) $(NAME_SERVER)
		$(RM) $(LIB)

re: fclean all

.PHONY: all clean fclean re
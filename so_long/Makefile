# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 15:10:36 by mokutucu          #+#    #+#              #
#    Updated: 2024/03/12 15:28:23 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc

CFLAGS = -Wall -Werror -Wextra -Imlx -g

# flags linking mlx library
MLXFLAGS = -L ./libs/mlxlib -lmlx -lXext -lX11

LIBS = ./libs/libft/libft.a

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	# Build mlx_linux and libft targets
	make -C ./libs/mlxlib
	make -C ./libs/libft

	# Link the executable
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)

clean:
	# Clean mlx_linux and libft targets
	make clean -C ./libs/mlxlib
	make clean -C ./libs/libft

	# Remove object files
	rm -rf $(OBJS)


fclean:
	# Fclean mlx_linux and libft targets
	make clean -C ./libs/mlxlib
	make fclean -C ./libs/libft

	# Remove object files and the target executable
	rm -rf $(OBJS)
	rm -rf $(NAME)


re: fclean all

.PHONY: all clean fclean re
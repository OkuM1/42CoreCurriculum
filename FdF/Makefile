# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 15:10:36 by mokutucu          #+#    #+#              #
#    Updated: 2024/04/05 16:34:14 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc

CFLAGS = -Wall -Werror -Wextra -Imlx -g

# flags linking mlx library
MLX_DIR = ./libs/mlxlib
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

MLXFLAGS = -L ./libs/mlxlib -lmlx -lXext -lX11 -lm

LIBS = ./libs/libft/libft.a

SRCS = fdf.c parse_map.c draw.c utils.c	utils2.c

OBJS = $(SRCS:.c=.o)

all: setup $(NAME)

setup: $(MLX_DIR)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(NAME): $(OBJS)
	# Build mlx_linux and libft targets
	make -C $(MLX_DIR)
	make -C ./libs/libft

	# Link the executable
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)

clean:
	# Clean mlx_linux and libft targets
	make clean -C $(MLX_DIR)
	make clean -C ./libs/libft

	# Remove object files
	rm -rf $(OBJS)

fclean: clean
	# Fclean mlx_linux and libft targets
	rm -rf $(MLX_DIR)
	make fclean -C ./libs/libft

	# Remove object files and the target executable
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re setup

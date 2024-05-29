# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 15:10:36 by mokutucu          #+#    #+#              #
#    Updated: 2024/05/10 15:26:02 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

CC		=	cc

CFLAGS =	-Wall -Wextra -Werror

RM		=	rm -rf

SRC_DIR	=	./src/

OBJ_DIR	=	./objs/

MLX_DIR =	./minilibx-linux/

MLX_REPO = https://github.com/42Paris/minilibx-linux.git

SRC		=	ft_main.c \
			ft_julia.c \
			ft_mandelbrot.c \
			ft_burning_ship.c \
			ft_checker.c \
			ft_pixel.c \
			ft_coords_and_limits.c \
			ft_viewport.c \
			ft_exit.c \
			ft_hooks.c \
			ft_zoom.c \
			ft_utils.c \

INCLUDE	=	-I $(MLX_DIR) -I ./include

LIBX    =	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm

OBJ		=	${addprefix ${OBJ_DIR}, ${SRC:.c=.o}}

all: $(NAME)

$(NAME): $(OBJ) $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBX) -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

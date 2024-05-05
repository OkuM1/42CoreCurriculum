# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 15:21:52 by mokutucu          #+#    #+#              #
#    Updated: 2024/05/05 15:44:52 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap
LIBDIR	= libs/libft/libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
SRC_DIR = src

SRCS	= $(addprefix $(SRC_DIR)/, error.c free.c init.c linked_list.c main.c min_max.c radix.c sort_moves_1.c sort_moves_2.c sort_moves_3.c tiny_sorts.c)
OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS) $(LIBDIR)
	$(CC) $(OBJS) $(LIBDIR) -o $(NAME) $(CFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIBDIR):
	@make -C libs/libft/
	@echo "compiled libft.a\n"

clean:
	$(RM) $(OBJS)
	@make clean -C libs/libft/

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libs/libft/

re: fclean all

.PHONY: all clean fclean re
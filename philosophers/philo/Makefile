# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 15:07:05 by mokutucu          #+#    #+#              #
#    Updated: 2024/11/04 16:55:40 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo

OBJDIR  = obj
CC      = cc

CFLAGS  = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

RM      = rm -rf

SRC_DIR = src
SRCS    = src/actions.c src/clean.c src/forks.c src/ft_atoll.c src/main.c src/monitor.c src/sim.c src/utils.c

OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all:    $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

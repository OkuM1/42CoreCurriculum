# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 16:08:54 by mokutucu          #+#    #+#              #
#    Updated: 2024/03/11 15:23:50 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_substr.c \
					ft_strlcat.c ft_strncmp.c ft_atoi.c  ft_isalpha.c \
					ft_memcpy.c ft_strchr.c  ft_strlcpy.c  ft_strjoin.c\
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c\
					ft_memmove.c ft_strdup.c  ft_strlen.c  ft_strrchr.c  ft_strtrim.c\
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c ft_split.c\
					ft_itoa.c ft_strmapi.c  ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
					ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c print_util1.c print_util2.c\
					get_next_line.c get_next_line_utils.c\



B_SRCS			= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
					ft_lstmap.c

OBJS			= $(SRCS:.c=.o)

B_OBJS			= $(B_SRCS:.c=.o)

CC				= cc

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a


all:			$(NAME)

$(NAME):		$(OBJS)
			ar rc $(NAME) $(OBJS)

bonus:			$(B_OBJS)
			ar rc $(NAME) $(B_OBJS)

clean:
	$(RM) $(OBJS) $(B_OBJS)
fclean: clean
	$(RM) $(NAME) $(bonus)
re: fclean all
.PHONY: all clean fclean re bonus

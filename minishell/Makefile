# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 15:07:05 by mokutucu          #+#    #+#              #
#    Updated: 2024/09/24 13:12:40 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell

LIBDIR  = libs/libft/libft.a
OBJDIR  = obj
CC      = cc

CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -lreadline

RM      = rm -rf

SRC_DIR = src
SRCS    = src/error.c src/init.c src/main.c src/shlvl.c src/debug_main.c \
		  src/0.garbage_collector/ft_gc_malloc.c \
		  src/1.lexer/ft_shell_split.c src/1.lexer/ft_split_redir.c \
		  src/1.lexer/lexer_utils.c src/1.lexer/split_redir_utils.c \
		  src/1.lexer/tokenizer.c src/1.syntax_check/pipe_syntax.c \
		  src/1.syntax_check/syntax_checker.c src/1.syntax_check/redirection_syntax.c src/1.syntax_check/or_syntax.c\
		  src/2.expansion/ft_shell_strdup.c src/2.expansion/calc_expand_len.c \
		  src/2.expansion/expand_env.c src/2.expansion/expand_string.c \
		  src/3.cmd_parser/commands.c src/3.cmd_parser/output_redir.c \
		  src/3.cmd_parser/populate.c \
		  src/3.cmd_parser/input_redir.c src/3.cmd_parser/process_arg_utils.c \
		  src/3.cmd_parser/heredoc.c \
		  src/4.built_in_functions/exit.c src/4.built_in_functions/pwd.c \
		  src/4.built_in_functions/unset.c src/4.built_in_functions/built_in_utils.c \
		  src/4.built_in_functions/export_utils_2.c src/4.built_in_functions/exec_built_ins.c \
		  src/4.built_in_functions/export.c src/4.built_in_functions/export_utils.c \
		  src/4.built_in_functions/echo.c src/4.built_in_functions/env.c \
		  src/4.built_in_functions/cd.c src/6.signals/signal_handler.c \
		  src/5.execution/utils.c src/5.execution/utils_2.c \
		  src/5.execution/exec_no_pipes.c src/5.execution/exec_pipes.c \
		  src/5.execution/execve_no_pipes.c src/5.execution/execve_pipes.c \
		  src/5.execution/execve_utils.c

OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all:    $(NAME)

$(NAME): $(OBJS) $(LIBDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBDIR)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(LIBDIR):
	@make -s -C libs/libft/

clean:
	@rm -rf $(OBJDIR)
	@make clean -C libs/libft/

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libs/libft/

re: fclean all

.PHONY: all clean fclean re

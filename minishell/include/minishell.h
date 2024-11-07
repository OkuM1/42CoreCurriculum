/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:36:35 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 16:08:03 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"

# include <stdlib.h>     // Standard C Library
# include <stdio.h>      // Standard C Library
# include <errno.h>      // Standard C Library
# include <string.h>     // Standard C Library
# include <stdbool.h>    // Standard C Library

# include <unistd.h>     // POSIX Library
# include <sys/types.h>  // POSIX Library
# include <sys/stat.h>   // POSIX Library
# include <sys/wait.h>   // POSIX Library
# include <sys/ioctl.h>  // POSIX Library
# include <fcntl.h>      // POSIX Library
# include <signal.h>     // POSIX Library
# include <bits/sigaction.h> // POSIX Library
# include <dirent.h>     // POSIX Library

# include <term.h>       // Termcap/Terminfo Library
# include <curses.h>     // Termcap/Terminfo Library
# include <ncurses.h>    // Termcap/Terminfo Library

# include <readline/readline.h>  // GNU Readline Library
# include <readline/history.h>   // GNU Readline Library

# include <termios.h>    // POSIX Terminal I/O Library

// Define exit status codes
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_PERMISSION_DENIED 126
# define EXIT_INVALID_COMMAND 2
# define EXIT_FORK_FAILED 1
# define EXIT_EXECVE_FAILED 1
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

// Forward declaration of t_shell for gc
typedef struct s_shell			t_shell;

// global variable for signal handling
extern int						g_sig;

// TokenType enum
typedef enum TokenType
{
	WORD,
	FLAGS,
	REDIRECTION_OUT,
	REDIRECTION_IN,
	REDIRECTION_APPEND,
	HEREDOC,
	PIPE,
	OR,
	DOUBLE_QUOTED_STRING,
	SINGLE_QUOTED_STRING,
	ENV_VARIABLE,
	END
}	t_TokenType;

// Argument struct
typedef struct s_arg
{
	char			*arg;
	t_TokenType		type;
	struct s_arg	*prev;
	struct s_arg	*next;
	bool			open;
}	t_arg;

// Command struct
typedef struct s_command
{
	char				*cmd_name;
	char				**flags;
	char				**args;
	struct s_command	*next;
	int					stdin_fd;
	int					stdout_fd;
	bool				append_mode;
	bool				valid;

}	t_command;

// Token struct
typedef struct s_token
{
	char		*arg;
	t_TokenType	type;
}	t_token;

// Garbage collector struct
typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

// Garbage collector struct with shell pointer
typedef struct s_gc
{
	t_garbage	*head;
	t_shell		*shell;
}	t_gc;

typedef struct s_expand_context
{
	t_shell	*shell;
	char	*input;
	int		exit_status;
	size_t	len;
	size_t	i;
	size_t	j;
	char	*result;
}	t_expand_context;

typedef struct s_params
{
	t_gc		*gc;
	const char	*s;
	char		**array;
	size_t		*index;
}	t_params;
// Main shell struct
typedef struct s_shell
{
	int			origin_lvl;
	t_arg		*args_head;
	t_gc		gc;
	char		**env;
	t_command	*cmds_head;
	int			exit_status;
}	t_shell;

//signal handling
void		handle_signals(char *mode);

// Function prototypes for garbage collector
void		ft_gc_init(t_gc *gc, t_shell *shell);
void		ft_gc_free(t_gc *gc);
void		*ft_gc_malloc(t_gc *gc, size_t size);
void		*ft_gc_realloc(t_gc *gc, void *ptr,
				size_t old_size, size_t new_size);

// Function prototypes for string manipulation
char		*ft_shell_strdup(t_gc *gc, const char *s);
char		*ft_shell_strndup(t_gc *gc, const char *s, size_t n);
char		*ft_shell_substr(t_gc *gc, const char *s,
				unsigned int start, size_t len);
char		*ft_shell_strjoin(t_gc *gc, char *s1, char *s2);

// split stuff
size_t		ft_words(char const *s, char c);
char		**ft_shell_split(t_gc *gc, const char *s, char c);
char		**ft_split_redirections(t_gc *gc, const char *s);

// Function prototypes for parsing
void		handle_quote_split(const char *s, size_t i, bool *quote);
void		skip_quoted_string(const char **s, bool *quote, char *quote_char);
void		assign(size_t *i, size_t *j, int *index, bool *quote);
int			ft_quotes_not_closed(const char *line);
char		*strip_quotes_redir_split(t_gc *gc, const char *str);
void		init_params(t_params *params, t_gc *gc,
				const char *s, char **array);
void		init_variables(size_t *i, size_t *start, bool *in_quote,
				char *quote_char);

// Expand environment variables
char		*ft_expand_env(t_shell *shell, char *env);
char		*ft_getenv(t_shell *shell, const char *name);
int			check_if_in_single_quote(char *input, size_t i);
size_t		calculate_expanded_length(t_shell *shell,
				char *input, int exit_status);
char		*expand_string(t_shell *shell, char *input, int exit_status);

// Syntax analysis
int			syntax_checker(t_arg *head);
int			pipe_syntax(t_arg *head);
int			redirection_syntax(t_arg *head);
int			or_syntax(t_arg *head);

// Function prototypes for command processing
t_arg		*tokenizer(t_shell *shell, char *input);
t_command	*create_command(t_gc *gc);
void		add_arg_to_command(t_command *cmd, const char *arg, t_gc *gc);
void		set_command_name(t_command *cmd, const char *name, t_gc *gc);
int			count_pipes_argstruct(t_arg *args_head);
int			count_pipes_cmdstruct(t_command *cmds_head);
t_command	*create_and_populate_commands(t_shell *shell, t_gc *gc,
				t_arg *args_head);
void		add_flag_to_command(t_command *cmd, const char *flag, t_gc *gc);
void		add_arg_to_command(t_command *cmd, const char *arg, t_gc *gc);
int			if_redir(t_arg *current_arg, t_command *current_cmd);
void		handle_arguments(t_command *cmd, t_arg *arg, t_gc *gc);
int			handle_arg(t_shell *shell, t_command *cmd, t_arg **arg, t_gc *gc);
void		print_commands(t_command *cmds_head);

// Function prototypes for redirection handling
int			handle_output_redirection(t_command *cmd, t_arg *arg);
int			handle_output_redirection_truncate(t_command *cmd, t_arg *arg);
int			handle_output_redirection_append(t_command *cmd, t_arg *arg);
int			handle_input_redirection(t_command *cmd, t_arg *arg);
int			handle_input_redirection_file(t_command *cmd, t_arg *arg);
int			handle_input_redirection_heredoc(t_command *cmd);
int			parse_heredoc(t_shell *shell, t_command *cmd, t_arg **arg);
int			delimiter_found(char *line, const char *delimiter);

// Function prototypes for built-in commands
int			is_built_in(char *cmd);
int			exec_built_ins(t_shell *shell, t_command *cmd);
int			built_in_cd(t_shell *shell);
int			built_in_pwd(t_shell *shell);
int			built_in_env(t_shell *shell);
int			built_in_echo(t_shell *shell, t_command *cmd);
int			ft_env_len(char **env);
char		*find_variable(t_gc *gc, const char *arg);
int			find_var_in_env(char **env, const char *var_name);
char		**add_env_var(t_gc *gc, char *arg, char **env, int env_len);
char		**change_or_add_env_var(t_gc *gc, char *arg, char **env);
int			built_in_export(t_shell *shell);
int			built_in_unset(t_shell *shell);
char		*strip_quotes(t_gc *gc, const char *str);
int			built_in_exit(t_shell *shell);
int			is_valid_identifier(const char *str);
void		print_export_env(t_gc *gc, char **env);
void		ft_sort(char **env, int len);
void		ft_swap(char **a, char **b);
int			count_flags(t_command *cmd);
int			count_args(t_command *cmd);
char		*ft_getcwd(t_gc *gc);

// Function prototypes for executing commands
int			execute_command_without_pipes(t_shell *shell, t_command *cmds_head);
int			execute_commands_with_pipes(t_shell *shell, t_command *cmds_head);
int			execute_command(t_shell *shell, t_command *cmd);
int			execute_command_no_pipes(t_shell *shell, t_command *cmd);
int			fork_and_execute_command(t_shell *shell, t_command *cmd,
				int *pipe_descriptors, int cmd_index);
char		*remove_quotes(t_gc *gc, const char *str);
char		*get_path(t_shell *shell, char *cmd);
int			is_directory(char *path);
int			count_arguments(char **args);
int			needs_piping(t_command *cmds_head);
void		setup_redirections(int cmd_index, int num_pipes,
				int *pipe_descriptors);
void		create_pipes(int num_pipes, int *pipe_descriptors);
void		close_pipes(int num_pipes, int *pipe_descriptors);
void		check_if_command_is_valid(t_command *cmd);
char		**prepare_args(t_shell *shell,
				t_command *cmd, int flags_count, int args_count);
int			handle_parent_process(pid_t pid);

// Error handling
void		perror_fork(void);
void		perror_malloc(void);
void		perror_strdup(void);
int			perror_pipe(void);
void		write_error(const char *msg, const char *arg);
t_arg		*tokenizer_error(t_shell *shell, char *input);

// Main
char		**init_env(char **envp, t_gc *gc);
void		init_shell(t_shell *shell, char **envp);
void		update_shlvl(t_shell *shell);
void		set_sig_exit(t_shell *shell, int sig);
void		execute_shell_is_piping_needed(t_shell *shell);
void		exit_status_and_free(t_shell *shell, char *line, int status);

// Debugging
void		print_cmd_args(char **args, const char *label);
void		print_commands(t_command *cmds_head);

#endif // MINISHELL_H

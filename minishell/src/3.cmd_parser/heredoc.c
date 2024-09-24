/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:47:54 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/24 13:12:29 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	heredoc_waitpid(t_shell *shell, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
		if (shell->exit_status == 130)
			g_sig = SIGINT;
		if (shell->exit_status)
			return (0);
	}
	return (1);
}

void	exit_heredoc(void)
{
	rl_clear_history();
	exit(0);
}

void	write_heredoc(t_shell *shell, int pipe_fd[2], char *delimiter)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("heredoc>");
		if (line == NULL || delimiter_found(line, delimiter) == 0)
		{
			if (line == NULL)
			{
				ft_putstr_fd("warning: here-document delimited", 2);
				exit_heredoc();
			}
			else
			{
				free(line);
				exit_heredoc();
			}
		}
		expanded_line = expand_string(shell, line, 0);
		free(line);
		write(pipe_fd[1], expanded_line, ft_strlen(expanded_line));
		write(pipe_fd[1], "\n", 1);
		free(expanded_line);
	}
}

int	heredoc(t_shell *shell, char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror_pipe());
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), 0);
	if (pid == 0)
	{
		handle_signals("heredoc");
		write_heredoc(shell, pipe_fd, delimiter);
	}
	else
	{
		close(pipe_fd[1]);
	}
	if (!heredoc_waitpid(shell, pid))
		return (1);
	return (pipe_fd[0]);
}

// Main function to parse and handle heredoc in a command
int	parse_heredoc(t_shell *shell, t_command *cmd, t_arg **arg)
{
	int		fd;
	char	*delimiter;

	if ((*arg)->type == HEREDOC)
	{
		delimiter = (*arg)->next->arg;
		fd = heredoc(shell, delimiter);
		if (fd == -2)
		{
			return (-2);
		}
		if (fd < 0)
		{
			perror("heredoc interrupted");
			return (1);
		}
		cmd->stdin_fd = fd;
		return (0);
	}
	return (0);
}

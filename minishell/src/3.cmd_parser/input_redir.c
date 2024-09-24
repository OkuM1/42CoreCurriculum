/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:47:57 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/19 21:18:22 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_input_redirection(t_command *cmd, t_arg *arg)
{
	if (arg->type == REDIRECTION_IN)
	{
		return (handle_input_redirection_file(cmd, arg));
	}
	else if (arg->type == HEREDOC)
	{
		return (handle_input_redirection_heredoc(cmd));
	}
	return (0);
}

int	handle_input_redirection_file(t_command *cmd, t_arg *arg)
{
	int	fd;

	if (cmd->stdin_fd != STDIN_FILENO)
	{
		close(cmd->stdin_fd);
	}
	fd = open(arg->next->arg, O_RDONLY);
	if (fd < 0)
	{
		perror("open input file");
		cmd->valid = false;
		return (1);
	}
	cmd->stdin_fd = fd;
	return (0);
}

int	handle_input_redirection_heredoc(t_command *cmd)
{
	if (cmd->stdin_fd != STDIN_FILENO)
	{
		if (dup2(cmd->stdin_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 stdin_fd");
			exit(EXIT_FAILURE);
		}
		close(cmd->stdin_fd);
	}
	if (cmd->stdout_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->stdout_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout_fd");
			exit(EXIT_FAILURE);
		}
		close(cmd->stdout_fd);
	}
	return (0);
}

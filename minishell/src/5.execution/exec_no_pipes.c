/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:58:43 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/20 15:59:49 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_fds(t_command *cmd)
{
	if (cmd->stdin_fd != STDIN_FILENO)
	{
		if (dup2(cmd->stdin_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 stdin");
			return (EXIT_FAILURE);
		}
		close(cmd->stdin_fd);
	}
	if (cmd->stdout_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->stdout_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout");
			return (EXIT_FAILURE);
		}
		close(cmd->stdout_fd);
	}
	return (EXIT_SUCCESS);
}

int	restore_file_descriptors(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
	{
		perror("dup2 saved_stdout");
		return (EXIT_FAILURE);
	}
	close(saved_stdout);
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
	{
		perror("dup2 saved_stdin");
		return (EXIT_FAILURE);
	}
	close(saved_stdin);
	return (EXIT_SUCCESS);
}

int	execute_command_without_pipes(t_shell *shell, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	status = 0;
	if (!cmd || ft_strlen(cmd->cmd_name) == 0)
		return (127);
	if (!cmd->valid)
		return (1);
	if (handle_fds(cmd))
		return (EXIT_FAILURE);
	if (is_built_in(cmd->cmd_name))
		status = exec_built_ins(shell, cmd);
	else
	{
		status = execute_command_no_pipes(shell, cmd);
		if (status == -1)
			status = 126;
	}
	if (restore_file_descriptors(saved_stdin, saved_stdout))
		return (EXIT_FAILURE);
	return (status);
}

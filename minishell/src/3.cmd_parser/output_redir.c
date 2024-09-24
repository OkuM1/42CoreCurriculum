/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:47:19 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/18 21:28:50 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_output_redirection(t_command *cmd, t_arg *arg)
{
	if (arg->type == REDIRECTION_OUT)
	{
		return (handle_output_redirection_truncate(cmd, arg));
	}
	else if (arg->type == REDIRECTION_APPEND)
	{
		return (handle_output_redirection_append(cmd, arg));
	}
	return (0);
}

int	handle_output_redirection_truncate(t_command *cmd, t_arg *arg)
{
	int	fd;

	if (cmd->stdout_fd != STDOUT_FILENO)
	{
		close(cmd->stdout_fd);
	}
	fd = open(arg->next->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		cmd->valid = false;
		return (1);
	}
	cmd->stdout_fd = fd;
	return (0);
}

int	handle_output_redirection_append(t_command *cmd, t_arg *arg)
{
	int	fd;

	if (cmd->stdout_fd != STDOUT_FILENO)
	{
		close(cmd->stdout_fd);
	}
	fd = open(arg->next->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		cmd->valid = false;
		return (1);
	}
	cmd->stdout_fd = fd;
	cmd->append_mode = true;
	return (0);
}

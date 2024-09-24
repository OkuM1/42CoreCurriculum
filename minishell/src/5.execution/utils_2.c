/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:25:51 by afoth             #+#    #+#             */
/*   Updated: 2024/09/20 14:46:20 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_if_command_is_valid(t_command *cmd)
{
	if (!cmd->valid)
	{
		if (cmd->next != NULL)
			exit(0);
		exit(1);
	}
}

int	count_flags(t_command *cmd)
{
	int	flag_count;

	flag_count = 0;
	while (cmd->flags && cmd->flags[flag_count])
		flag_count++;
	return (flag_count);
}

int	count_args(t_command *cmd)
{
	int	args_count;

	args_count = 0;
	while (cmd->args && cmd->args[args_count])
		args_count++;
	return (args_count);
}

int	handle_parent_process(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

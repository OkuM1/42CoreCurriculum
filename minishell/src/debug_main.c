/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:13:58 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 16:05:57 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tokens(t_arg *head)
{
	t_arg	*current;

	current = head;
	while (current)
	{
		printf("arg: %s, type: %d\n", current->arg, current->type);
		current = current->next;
	}
}

void	print_cmd_args(char **args, const char *label)
{
	int	i;

	if (args)
	{
		printf("%s:\n", label);
		i = 0;
		while (args[i])
		{
			printf("  Arg %d: %s\n", i, args[i]);
			i++;
		}
	}
	else
	{
		printf("%s: NULL\n", label);
	}
}

void	print_commands(t_command *cmds_head)
{
	t_command	*cmd;

	cmd = cmds_head;
	while (cmd)
	{
		printf("Command:\n");
		printf("  stdin_fd: %d\n", cmd->stdin_fd);
		printf("  stdout_fd: %d\n", cmd->stdout_fd);
		if (cmd->append_mode)
			printf("  Append mode: true\n");
		else
			printf("  Append mode: false\n");
		printf("  Command name: %s\n", cmd->cmd_name);
		print_cmd_args(cmd->flags, "Flags");
		print_cmd_args(cmd->args, "Args");
		cmd = cmd->next;
		printf("-----\n");
	}
}

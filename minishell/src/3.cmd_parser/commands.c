/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:59:47 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 13:25:24 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Creates a new command node with default values.
 */
t_command	*create_command(t_gc *gc)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)ft_gc_malloc(gc, sizeof(t_command));
	if (!new_cmd)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	new_cmd->cmd_name = NULL;
	new_cmd->flags = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	new_cmd->stdin_fd = STDIN_FILENO;
	new_cmd->stdout_fd = STDOUT_FILENO;
	new_cmd->append_mode = false;
	new_cmd->valid = true;
	return (new_cmd);
}

/*
 * Creates an array of command nodes and links them together.
 */
static t_command	**create_command_list(t_gc *gc, int pipe_count)
{
	t_command	**commands;
	int			i;

	commands = ft_gc_malloc(gc, (pipe_count + 1) * sizeof(t_command *));
	if (!commands)
		return (NULL);
	i = 0;
	while (i <= pipe_count)
	{
		commands[i] = create_command(gc);
		if (!commands[i])
		{
			return (NULL);
		}
		i++;
	}
	return (commands);
}

/*
 * Links command nodes in the array.
 */
static void	link_commands(t_command **commands, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		commands[i]->next = commands[i + 1];
		i++;
	}
}

static int	process_arguments(t_shell *shell, t_command *cmds_head,
	t_arg *args_head, t_gc *gc)
{
	t_command	*current_cmd;
	t_arg		*current_arg;

	current_cmd = cmds_head;
	current_arg = args_head;
	while (current_arg->type != END)
	{
		if (handle_arg(shell, current_cmd, &current_arg, gc) == 1)
			return (1);
		if (current_arg && current_arg->type == PIPE)
			current_cmd = current_cmd->next;
	}
	return (0);
}

t_command	*create_and_populate_commands(t_shell *shell,
	t_gc *gc, t_arg *args_head)
{
	int			pipe_count;
	t_command	**commands;
	t_command	*cmds_head;

	pipe_count = count_pipes_argstruct(args_head);
	commands = create_command_list(gc, pipe_count);
	if (!commands)
		return (NULL);
	link_commands(commands, pipe_count);
	cmds_head = commands[0];
	if (process_arguments(shell, cmds_head, args_head, gc) == 1)
		return (NULL);
	return (cmds_head);
}

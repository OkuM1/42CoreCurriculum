/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:04:33 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/18 21:45:16 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
 * Counts the number of PIPE tokens in the argument list.
 */
int	count_pipes_argstruct(t_arg *args_head)
{
	int		pipe_count;
	t_arg	*current_arg;

	pipe_count = 0;
	current_arg = args_head;
	while (current_arg)
	{
		if (current_arg->type == PIPE)
			pipe_count++;
		current_arg = current_arg->next;
	}
	return (pipe_count);
}

void	add_flag_to_command(t_command *cmd, const char *flag, t_gc *gc)
{
	int		count;
	char	**new_flags;
	int		i;

	count = 0;
	if (cmd->flags)
	{
		while (cmd->flags[count])
			count++;
	}
	new_flags = (char **)ft_gc_malloc(gc, sizeof(char *) * (count + 2));
	if (!new_flags)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		new_flags[i] = cmd->flags[i];
		i++;
	}
	new_flags[count] = ft_shell_strdup(gc, flag);
	new_flags[count + 1] = NULL;
	cmd->flags = new_flags;
}

void	add_arg_to_command(t_command *cmd, const char *arg, t_gc *gc)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = (char **)ft_gc_malloc(gc, sizeof(char *) * (count + 2));
	if (!new_args)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = ft_shell_strdup(gc, arg);
	new_args[count + 1] = NULL;
	cmd->args = new_args;
}

void	set_command_name(t_command *cmd, const char *name, t_gc *gc)
{
	if (cmd->cmd_name == NULL)
		cmd->cmd_name = ft_shell_strdup(gc, name);
}

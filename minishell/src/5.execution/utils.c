/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:00:49 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/18 21:10:14 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to count arguments
int	count_arguments(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

// Function to count the number of pipes needed based on the command structure
int	count_pipes_cmdstruct(t_command *cmds_head)
{
	int	count;

	count = 0;
	while (cmds_head && cmds_head->next)
	{
		count++;
		cmds_head = cmds_head->next;
	}
	return (count);
}

// Set up redirections for a given command in the pipeline
void	setup_redirections(int cmd_index, int num_pipes, int *pipe_descriptors)
{
	if (cmd_index > 0)
	{
		if (dup2(pipe_descriptors[(cmd_index - 1) * 2], STDIN_FILENO) < 0)
		{
			perror("dup2 stdin");
			exit(EXIT_FAILURE);
		}
	}
	if (cmd_index < num_pipes)
	{
		if (dup2(pipe_descriptors[cmd_index * 2 + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2 stdout");
			exit(EXIT_FAILURE);
		}
	}
}

// Create pipes for the specified number of pipes
void	create_pipes(int num_pipes, int *pipe_descriptors)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_descriptors + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

// Close all pipe descriptors
void	close_pipes(int num_pipes, int *pipe_descriptors)
{
	int	i;

	i = 0;
	while (i < num_pipes * 2)
	{
		close(pipe_descriptors[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:51:22 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/18 15:42:02 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// Function to check for initial -n flags in the flags array
bool	check_initial_n_flag(char **flags)
{
	int		i;
	bool	suppress_newline;

	if (!flags)
		return (false);
	i = 0;
	suppress_newline = false;
	while (flags[i])
	{
		if (ft_strcmp(flags[i], "-n") == 0)
		{
			suppress_newline = true;
		}
		else
		{
			break ;
		}
		i++;
	}
	return (suppress_newline);
}

// Function to print echo arguments without quote processing
static void	print_echo_arguments(t_gc *gc, char **args, bool skip_n_flag)
{
	int		i;
	char	*arg;

	if (!args)
		return ;
	i = 0;
	if (skip_n_flag && ft_strcmp(args[i], "-n") == 0)
	{
		i++;
	}
	while (args[i])
	{
		arg = ft_shell_strdup(gc, args[i]);
		if (arg)
			write(STDOUT_FILENO, arg, ft_strlen(arg));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
}

int	built_in_echo(t_shell *shell, t_command *cmd)
{
	bool	suppress_newline;

	if (!cmd)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	suppress_newline = check_initial_n_flag(cmd->flags);
	print_echo_arguments(&shell->gc, cmd->args, suppress_newline);
	if (!suppress_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

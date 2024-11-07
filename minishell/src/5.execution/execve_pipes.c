/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:16:51 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:45:26 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_shell *shell, t_command *cmd)
{
	int		flags_count;
	int		args_count;
	char	**args;
	char	*path;

	flags_count = count_flags(cmd);
	args_count = count_args(cmd);
	args = prepare_args(shell, cmd, flags_count, args_count);
	path = get_path(shell, args[0]);
	if (is_directory(args[0]) == 1)
		exit(EXIT_PERMISSION_DENIED);
	if (path == NULL || execve(path, args, shell->env) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (EXIT_COMMAND_NOT_FOUND);
	}
	return (EXIT_SUCCESS);
}

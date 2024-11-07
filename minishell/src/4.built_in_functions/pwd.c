/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:05:32 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/22 16:10:28 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Return codes
#define PWD_SUCCESS 0
#define PWD_ERROR 1

int	pwd_error(char *error_message)
{
	ft_putstr_fd("pwd: ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (PWD_ERROR);
}

int	built_in_pwd(t_shell *shell)
{
	char	*current_dir;
	int		index;

	if (shell->cmds_head->args || shell->cmds_head->flags)
		pwd_error("no options allowed");
	else if (!shell || !shell->env)
		pwd_error("no environment variables found");
	else
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			return (PWD_ERROR);
		write(STDOUT_FILENO, current_dir, ft_strlen(current_dir));
		write(STDOUT_FILENO, "\n", 1);
		index = find_var_in_env(shell->env, "PWD");
		if (index != -1)
			shell->env = change_or_add_env_var
				(&shell->gc, ft_shell_strjoin
					(&shell->gc, "PWD=", current_dir), shell->env);
		free(current_dir);
		return (PWD_SUCCESS);
	}
	return (PWD_ERROR);
}

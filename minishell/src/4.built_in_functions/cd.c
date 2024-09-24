/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:51:53 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:47:29 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_oldpwd(t_gc *gc, char **oldpwd)
{
	*oldpwd = ft_getcwd(gc);
	if (!(*oldpwd))
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}

char	*get_target_dir(t_shell *shell)
{
	int	index;

	if (shell->cmds_head->args && shell->cmds_head->args[0])
		return (shell->cmds_head->args[0]);
	index = find_var_in_env(shell->env, "HOME");
	if (index != -1)
		return (ft_strchr(shell->env[index], '=') + 1);
	ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	return (NULL);
}

int	change_directory(char *target_dir)
{
	if (access(target_dir, F_OK) != 0)
	{
		ft_putstr_fd("cd: No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	update_env_vars(t_shell *shell, char *oldpwd, char *newpwd)
{
	shell->env = change_or_add_env_var(&shell->gc,
			ft_shell_strjoin(&shell->gc, "OLDPWD=", oldpwd), shell->env);
	shell->env = change_or_add_env_var(&shell->gc,
			ft_shell_strjoin(&shell->gc, "PWD=", newpwd), shell->env);
	return (0);
}

int	built_in_cd(t_shell *shell)
{
	char	*target_dir;
	char	*oldpwd;
	char	*newpwd;

	if (shell->cmds_head->args && shell->cmds_head->args[1])
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (set_oldpwd(&shell->gc, &oldpwd) != 0)
		return (1);
	target_dir = get_target_dir(shell);
	if (!target_dir)
	{
		return (1);
	}
	if (change_directory(target_dir) != 0)
	{
		return (1);
	}
	newpwd = ft_getcwd(&shell->gc);
	update_env_vars(shell, oldpwd, newpwd);
	return (0);
}

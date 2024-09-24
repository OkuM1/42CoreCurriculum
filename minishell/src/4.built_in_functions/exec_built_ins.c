/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:36:35 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/18 20:34:34 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// Function to check if a command is a built-in
int	is_built_in(char *arg)
{
	if (ft_strcmp(arg, "cd") == 0)
		return (1);
	if (ft_strcmp(arg, "echo") == 0)
		return (1);
	if (ft_strcmp(arg, "pwd") == 0)
		return (1);
	if (ft_strcmp(arg, "env") == 0)
		return (1);
	if (ft_strcmp(arg, "export") == 0)
		return (1);
	if (ft_strcmp(arg, "unset") == 0)
		return (1);
	if (ft_strcmp(arg, "exit") == 0)
		return (1);
	return (0);
}

int	exec_built_ins(t_shell *shell, t_command *cmd)
{
	char	*cmd_name;
	int		status;

	status = 0;
	if (cmd == NULL || cmd->cmd_name == NULL)
		return (1);
	cmd_name = cmd->cmd_name;
	if (ft_strcmp(cmd_name, "cd") == 0)
		status = built_in_cd(shell);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		status = built_in_echo(shell, cmd);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		status = built_in_pwd(shell);
	else if (ft_strcmp(cmd_name, "env") == 0)
		status = built_in_env(shell);
	else if (ft_strcmp(cmd_name, "export") == 0)
		status = built_in_export(shell);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		status = built_in_unset(shell);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		status = built_in_exit(shell);
	else
		return (1);
	return (status);
}

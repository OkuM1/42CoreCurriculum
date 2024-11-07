/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_no_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:26:15 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:01:29 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_flags(t_shell *shell, t_command *cmd, char **args, int flags_count)
{
	int	i;

	i = 0;
	while (i < flags_count)
	{
		args[i + 1] = ft_shell_strdup(&shell->gc, cmd->flags[i]);
		if (!args[i + 1])
			perror_strdup();
		i++;
	}
}

char	**prepare_args(t_shell *shell,
	t_command *cmd, int flags_count, int args_count)
{
	char	**args;
	int		j;

	args = (char **)ft_gc_malloc
		(&shell->gc, sizeof(char *) * (flags_count + args_count + 2));
	if (!args)
		perror_malloc();
	fill_flags(shell, cmd, args, flags_count);
	args[0] = ft_shell_strdup(&shell->gc, cmd->cmd_name);
	if (!args[0])
		perror_strdup();
	j = 0;
	while (j < args_count)
	{
		args[flags_count + 1 + j] = remove_quotes
			(&shell->gc, ft_shell_strdup(&shell->gc, cmd->args[j]));
		if (!args[flags_count + 1 + j])
			perror_strdup();
		j++;
	}
	args[flags_count + args_count + 1] = NULL;
	return (args);
}

int	is_directory(char *arg)
{
	DIR	*dir;

	dir = opendir(arg);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	execute_child_process(t_shell *shell, t_command *cmd)
{
	int		flags_count;
	int		args_count;
	char	**args;
	char	*path;

	flags_count = count_flags(cmd);
	args_count = count_args(cmd);
	args = prepare_args(shell, cmd, flags_count, args_count);
	if (is_directory(args[0]) == 1)
		exit(EXIT_PERMISSION_DENIED);
	path = get_path(shell, args[0]);
	if (!path)
	{
		write(2, "command not found", 17);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	execve(path, args, shell->env);
	perror("execve");
	exit(EXIT_EXECVE_FAILED);
}

int	execute_command_no_pipes(t_shell *shell, t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strcmp(cmd->cmd_name, "./minishell") == 0)
			handle_signals("interactive");
		else
			handle_signals("noninteractive");
		execute_child_process(shell, cmd);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	return (handle_parent_process(pid));
}

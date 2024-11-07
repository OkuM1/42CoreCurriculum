/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:51:15 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:30:36 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(t_gc *gc, const char *str)
{
	char	*result;
	int		i;
	int		j;

	result = (char *)ft_gc_malloc(gc, (ft_strlen(str) + 1));
	if (!result)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			result[j++] = str[i];
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_getenv(t_shell *shell, const char *name)
{
	char	**environ;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	environ = shell->env;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (&environ[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

char	*normalize_path(t_shell *shell, char *path)
{
	if (path[0] == '/' || (path[0] == '.'
			&& (path[1] == '/' || path[1] == '.')))
	{
		if (access(path, F_OK) != 0)
		{
			write_error("No such file or directory: ", path);
			exit(EXIT_COMMAND_NOT_FOUND);
		}
		if (is_directory(path))
		{
			exit(EXIT_PERMISSION_DENIED);
		}
		if (access(path, X_OK) != 0)
		{
			write_error("Permission denied: ", path);
			exit(EXIT_PERMISSION_DENIED);
		}
		return (ft_shell_strdup(&shell->gc, path));
	}
	return (ft_shell_strdup(&shell->gc, path));
}

char	*find_executable_path(t_shell *shell, char **path_split, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (path_split[i])
	{
		path = ft_shell_strjoin(&shell->gc, path_split[i], "/");
		path = ft_shell_strjoin(&shell->gc, path, cmd);
		if (access(path, F_OK) == 0)
		{
			if (is_directory(path))
				exit(EXIT_PERMISSION_DENIED);
			if (access(path, X_OK) == 0)
				return (path);
			write_error("Permission denied: ", path);
			exit(EXIT_PERMISSION_DENIED);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(t_shell *shell, char *cmd)
{
	char	*path_env;
	char	**path_split;
	char	*executable_path;

	if (cmd[0] == '.' || cmd[0] == '/')
		return (normalize_path(shell, cmd));
	path_env = ft_getenv(shell, "PATH");
	if (!path_env)
		exit(EXIT_COMMAND_NOT_FOUND);
	path_split = ft_shell_split(&shell->gc, path_env, ':');
	executable_path = find_executable_path(shell, path_split, cmd);
	if (!executable_path)
	{
		write_error("Command not found: ", cmd);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	return (executable_path);
}

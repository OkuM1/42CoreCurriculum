/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:45:00 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/18 17:12:24 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Helper function to remove an environment variable from the environment array
char	**remove_env_var(t_gc *gc, char **env, int index)
{
	int		i;
	int		j;
	int		env_len;
	char	**new_env;

	i = 0;
	j = 0;
	env_len = ft_env_len(env);
	new_env = ft_gc_malloc(gc, sizeof(char *) * env_len);
	if (!new_env)
	{
		write(STDERR_FILENO, "unset: memory allocation failed\n", 32);
		return (env);
	}
	while (i < env_len)
	{
		if (i != index)
		{
			new_env[j] = env[i];
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	built_in_unset(t_shell *shell)
{
	t_gc	*gc;
	char	**args;
	char	**env;
	int		var_index;
	int		i;

	gc = &shell->gc;
	env = shell->env;
	args = shell->cmds_head->args;
	if (!args || !args[0])
		return (0);
	i = 0;
	while (args[i])
	{
		var_index = find_var_in_env(env, args[i]);
		if (var_index != -1)
			env = remove_env_var(gc, env, var_index);
		i++;
	}
	shell->env = env;
	return (0);
}

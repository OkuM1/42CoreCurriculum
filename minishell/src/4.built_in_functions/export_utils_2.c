/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:01:00 by afoth             #+#    #+#             */
/*   Updated: 2024/09/18 17:05:05 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Swap two strings in an array
void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Selection sort to sort environment variables alphabetically
void	ft_sort(char **env, int len)
{
	int	i;
	int	j;
	int	min_idx;

	i = 0;
	while (i < len - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[j], env[min_idx]) < 0)
			{
				min_idx = j;
			}
			j++;
		}
		ft_swap(&env[i], &env[min_idx]);
		i++;
	}
}

void	print_export_env(t_gc *gc, char **env)
{
	int		env_len;
	char	**sorted_env;
	int		i;

	env_len = ft_env_len(env);
	sorted_env = (char **)ft_gc_malloc(gc, sizeof(char *) * (env_len + 1));
	if (!sorted_env)
	{
		perror("Failed to allocate memory for sorted environment");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < env_len)
	{
		sorted_env[i] = ft_shell_strdup(gc, env[i]);
		i++;
	}
	sorted_env[env_len] = NULL;
	ft_sort(sorted_env, env_len);
	i = 0;
	while (i < env_len)
	{
		ft_printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
}

// Helper function to check if a string
// is a valid environment variable identifier
int	is_valid_identifier(const char *str)
{
	if (!str || !*str || (!ft_isalpha((unsigned char)*str) && *str != '_'))
		return (0);
	while (*str)
	{
		if (!ft_isalnum((unsigned char)*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

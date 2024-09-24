/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:55:59 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/19 21:29:37 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to expand environment variable from custom shell environment
// Find the environment variable in the custom environment

char	*ft_expand_env(t_shell *shell, char *env)
{
	int		index;
	char	*value;

	value = NULL;
	index = find_var_in_env(shell->env, env);
	if (index != -1)
	{
		value = ft_strchr(shell->env[index], '=') + 1;
		return (ft_shell_strdup(&shell->gc, value));
	}
	else
	{
		return (ft_shell_strdup(&shell->gc, ""));
	}
}

int	check_if_in_single_quote(char *input, size_t i)
{
	int		in_single_quote;
	int		in_double_quote;
	size_t	j;

	in_single_quote = 0;
	in_double_quote = 0;
	j = 0;
	while (j < i)
	{
		if (input[j] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[j] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		j++;
	}
	return (in_single_quote);
}

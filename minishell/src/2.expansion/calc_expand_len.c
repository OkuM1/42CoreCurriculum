/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_expand_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:55:59 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:47:52 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	calculate_exit_status_length(int exit_status)
{
	char	*exit_status_str;
	size_t	length;

	exit_status_str = ft_itoa(exit_status);
	if (!exit_status_str)
		return (0);
	length = ft_strlen(exit_status_str);
	free(exit_status_str);
	return (length);
}

static size_t	calculate_env_var_length(t_shell *shell, char *input, size_t *i)
{
	size_t	start;
	size_t	length;
	char	*env;
	char	*expanded;

	start = *i + 1;
	while (input[start] && (isalnum(input[start]) || input[start] == '_'))
		start++;
	env = ft_shell_substr(&shell->gc, input, (*i + 1), (start - *i - 1));
	expanded = ft_expand_env(shell, env);
	length = ft_strlen(expanded);
	*i = start;
	return (length);
}

static size_t	handle_dollar_length(t_shell *shell, char *input,
	size_t *i, int exit_status)
{
	size_t	len;

	len = 0;
	if (input[*i + 1] == '?')
	{
		len = calculate_exit_status_length(exit_status);
		*i += 2;
	}
	else if (isalnum(input[*i + 1]) || input[*i + 1] == '_')
	{
		len = calculate_env_var_length(shell, input, i);
	}
	else
	{
		len = 1;
		(*i)++;
	}
	return (len);
}

size_t	calculate_expanded_length(t_shell *shell, char *input,
	int exit_status)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '$')
			len += handle_dollar_length(shell, input, &i, exit_status);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

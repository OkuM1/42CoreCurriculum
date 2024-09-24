/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:04:38 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/18 16:42:44 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_params(t_params *params, t_gc *gc, const char *s, char **array)
{
	params->gc = gc;
	params->s = s;
	params->array = array;
}

void	init_variables(size_t *i, size_t *start, bool *in_quote,
		char *quote_char)
{
	*i = 0;
	*start = 0;
	*in_quote = false;
	*quote_char = 0;
}

/* Function to remove quotes from a string.
It removes both single and double quotes while keeping the content inside intact.
 */
char	*strip_quotes_redir_split(t_gc *gc, const char *str)
{
	char	*result;
	size_t	i;
	size_t	j;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	j = 0;
	in_single_quote = false;
	in_double_quote = false;
	result = ft_gc_malloc(gc, ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

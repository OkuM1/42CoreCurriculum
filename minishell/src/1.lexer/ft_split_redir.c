/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:35:01 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 16:46:23 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_quotes(char c, bool *in_quote, char *quote_char)
{
	if (!(*in_quote))
	{
		*in_quote = true;
		*quote_char = c;
	}
	else if (c == *quote_char)
	{
		*in_quote = false;
		*quote_char = 0;
	}
}

static void	handle_token(t_params *params, size_t start, size_t end)
{
	char	*token;

	if (end > start)
	{
		token = ft_shell_strndup(params->gc, params->s + start, end - start);
		params->array[*(params->index)] = strip_quotes_redir_split
			(params->gc, token);
		(*(params->index))++;
	}
}

static void	handle_special_chars(t_params *params, size_t *i)
{
	size_t	len;
	size_t	j;
	char	*dst;

	if (params->s[*i] == params->s[*i + 1])
	{
		len = 2;
	}
	else
	{
		len = 1;
	}
	dst = ft_gc_malloc(params->gc, len + 1);
	if (!dst)
		return ;
	j = 0;
	while (j < len)
	{
		dst[j] = params->s[*i + j];
		j++;
	}
	dst[len] = '\0';
	params->array[*(params->index)] = dst;
	(*(params->index))++;
	*i += (len - 1);
}

void	ft_handle_redir(t_gc *gc, const char *s, char **array, size_t *index)
{
	t_params	params;
	size_t		i;
	size_t		start;
	bool		in_quote;
	char		quote_char;

	init_params(&params, gc, s, array);
	params.index = index;
	init_variables(&i, &start, &in_quote, &quote_char);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			handle_quotes(s[i], &in_quote, &quote_char);
		if (!in_quote && (s[i] == '<' || s[i] == '>'
				|| s[i] == '|' || s[i] == ' '))
		{
			handle_token(&params, start, i);
			if (s[i] != ' ')
				handle_special_chars(&params, &i);
			start = i + 1;
		}
		i++;
	}
	handle_token(&params, start, i);
}

/*
 * Splits the input string into tokens while handling redirections and quotes.
 * Add some buffer for additional tokens (like redirection)
 */
char	**ft_split_redirections(t_gc *gc, const char *s)
{
	char	**array;
	size_t	num_tokens;
	size_t	index;

	index = 0;
	if (!s)
		return (NULL);
	num_tokens = ft_words(s, ' ') + 420;
	array = ft_gc_malloc(gc, num_tokens * sizeof(char *));
	if (!array)
		return (NULL);
	ft_handle_redir(gc, s, array, &index);
	array[index] = NULL;
	return (array);
}

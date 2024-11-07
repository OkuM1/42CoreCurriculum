/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:07:35 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 16:57:14 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_quotes(char c, bool *in_quote, char *quote_char)
{
	if (c == '\'' || c == '\"')
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
}

size_t	ft_words(char const *s, char c)
{
	size_t	count;
	bool	in_quote;
	char	quote_char;

	count = 0;
	in_quote = false;
	quote_char = 0;
	while (*s)
	{
		handle_quotes(*s, &in_quote, &quote_char);
		if (*s == c && !in_quote)
			count++;
		s++;
	}
	if (in_quote)
		return (count + 1);
	return (count);
}

void	*ft_allocate(t_gc *gc, const char *s, int start, int end)
{
	char	*word;

	word = ft_gc_malloc(gc, end - start + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, s + start, end - start);
	word[end - start] = '\0';
	return (word);
}

char	**ft_shell_split(t_gc *gc, const char *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	bool	quote;
	int		index;

	array = ft_gc_malloc(gc, ((ft_words(s, c) + 2) * sizeof(char *)));
	if (!array)
		return (NULL);
	assign(&i, &j, &index, &quote);
	while (i <= ft_strlen(s))
	{
		handle_quote_split(s, i, &quote);
		if ((s[i] != c || quote == true) && index < 0)
			index = i;
		else if (((s[i] == c && quote == false) \
		|| i == ft_strlen(s)) && index >= 0)
		{
			array[j++] = ft_allocate(gc, s, index, i);
			index = -1;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

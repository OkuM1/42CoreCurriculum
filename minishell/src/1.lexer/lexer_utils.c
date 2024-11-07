/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:53:40 by afoth             #+#    #+#             */
/*   Updated: 2024/09/21 18:10:17 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_quote_split(const char *s, size_t i, bool *quote)
{
	static char	quote_char;

	quote_char = 0;
	if (s[i] == '\'' || s[i] == '\"')
	{
		if (*quote == false)
		{
			*quote = true;
			quote_char = s[i];
		}
		else if (*quote == true && s[i] == quote_char)
		{
			*quote = false;
			quote_char = 0;
		}
	}
}

void	skip_quoted_string(const char **s, bool *quote, char *quote_char)
{
	if (**s == '\'' || **s == '\"')
	{
		*quote = !(*quote);
		*quote_char = **s;
		(*s)++;
	}
}

void	assign(size_t *i, size_t *j, int *index, bool *quote)
{
	*i = 0;
	*j = 0;
	*index = -1;
	*quote = false;
}

int	ft_quotes_not_closed(const char *line)
{
	bool	in_single_quote;
	bool	in_double_quote;
	size_t	i;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (line[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_single_quote || in_double_quote)
	{
		write(2, "minishell: syntax error: quotes not closed\n", 44);
		return (1);
	}
	return (0);
}

t_arg	*tokenizer_error(t_shell *shell, char *input)
{
	write(STDERR_FILENO, input, ft_strlen(input));
	shell->exit_status = 1;
	return (NULL);
}

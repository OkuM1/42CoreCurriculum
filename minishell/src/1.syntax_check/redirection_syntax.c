/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:59:28 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/22 14:51:33 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirection_input_syntax_check(t_arg *tmp)
{
	if (!tmp->next || !tmp->prev || tmp->next->type == END)
	{
		write_error("redirection input error:"
			" no arguments before or after redirection", tmp->arg);
		return (1);
	}
	if (tmp->next->type != WORD && tmp->next->type != DOUBLE_QUOTED_STRING)
	{
		write_error("redirection input error:"
			" no valid file name after redirection", tmp->arg);
		return (1);
	}
	if (tmp->prev->type != WORD)
	{
		write_error("redirection input error:"
			" no valid argument before redirection", tmp->arg);
		return (1);
	}
	return (0);
}

int	redirection_output_syntax_check(t_arg *tmp)
{
	if (!tmp->next || tmp->next->type == END)
	{
		write_error("redirection output error:"
			" no arguments before redirection", tmp->arg);
		return (1);
	}
	if (tmp->next->type != WORD)
	{
		write_error("redirection output error:"
			" no valid file name after redirection", tmp->arg);
		return (1);
	}
	return (0);
}

int	redirection_heredoc_syntax_check(t_arg *tmp)
{
	if (tmp->next)
	{
		if (tmp->next->type != WORD)
		{
			write_error("redirection error:"
				" no valid file name after redirection", tmp->arg);
			return (1);
		}
	}
	if (!tmp->prev && !tmp->next)
	{
		write_error("redirection error:"
			" no valid argument before or after redirection", tmp->arg);
		return (1);
	}
	return (0);
}

// check for syntax errors in redirections
int	redirection_syntax(t_arg *head)
{
	t_arg	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == REDIRECTION_IN)
		{
			if (redirection_input_syntax_check(tmp))
				return (1);
		}
		if (tmp->type == REDIRECTION_OUT)
		{
			if (redirection_output_syntax_check(tmp))
				return (1);
		}
		if (tmp->type == REDIRECTION_APPEND || tmp->type == HEREDOC)
		{
			if (redirection_heredoc_syntax_check(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:31:22 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:47:11 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_exit_status(int exit_status, char *result, size_t *j)
{
	char	*expanded;

	expanded = ft_itoa(exit_status);
	if (expanded)
	{
		ft_strlcpy(result + *j, expanded, ft_strlen(expanded) + 1);
		*j += ft_strlen(expanded);
		free(expanded);
	}
}

static char	*extract_env_var(t_shell *shell, char *input, size_t start)
{
	size_t	end;

	end = start;
	while (input[end] && (isalnum(input[end]) || input[end] == '_'))
		end++;
	return (ft_shell_substr(&shell->gc, input, start, end - start));
}

static void	handle_env_var(t_shell *shell, t_expand_context *ctx)
{
	size_t	start;
	char	*env;
	char	*expanded;

	start = ctx->i + 1;
	env = extract_env_var(shell, ctx->input, start);
	expanded = ft_expand_env(ctx->shell, env);
	ft_strlcpy(ctx->result + ctx->j, expanded, ctx->len - ctx->j + 1);
	ctx->j += ft_strlen(expanded);
	ctx->i = start + ft_strlen(env);
}

static void	process_characters(t_shell *shell, t_expand_context *ctx)
{
	while (ctx->input[ctx->i])
	{
		if (ctx->input[ctx->i] == '$'
			&& !check_if_in_single_quote(ctx->input, ctx->i))
		{
			if (ctx->input[ctx->i + 1] == '?')
			{
				handle_exit_status(ctx->exit_status, ctx->result, &ctx->j);
				ctx->i += 2;
			}
			else if (isalnum(ctx->input[ctx->i + 1])
				|| ctx->input[ctx->i + 1] == '_')
				handle_env_var(shell, ctx);
			else
			{
				ctx->result[ctx->j++] = '$';
				ctx->i++;
			}
		}
		else
		{
			ctx->result[ctx->j++] = ctx->input[ctx->i++];
		}
	}
}

char	*expand_string(t_shell *shell, char *input, int exit_status)
{
	t_expand_context	ctx;

	if (!input)
		return (NULL);
	ctx.shell = shell;
	ctx.input = input;
	ctx.exit_status = exit_status;
	ctx.i = 0;
	ctx.j = 0;
	ctx.len = calculate_expanded_length(shell, input, exit_status);
	ctx.result = (char *)ft_gc_malloc
		(&shell->gc, (sizeof(char) * (ctx.len + 1)));
	if (!ctx.result)
		return (NULL);
	process_characters(shell, &ctx);
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}

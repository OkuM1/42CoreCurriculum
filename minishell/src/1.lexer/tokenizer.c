/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:09:46 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 16:05:35 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Mapping struct for token types that are required by subject pdf

t_TokenType	get_token_type(const char *arg)
{
	int				i;
	const t_token	typemap[] = {
	{"|", PIPE}, {"\"", DOUBLE_QUOTED_STRING}, {"'", SINGLE_QUOTED_STRING},
	{"$", ENV_VARIABLE}, {"<<", HEREDOC}, {">>", REDIRECTION_APPEND},
	{"<", REDIRECTION_IN},	{">", REDIRECTION_OUT},
	{"||", OR}, {NULL, END}, {NULL, WORD}};

	i = 0;
	if (ft_strcmp(arg, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(arg, ">>") == 0)
		return (REDIRECTION_APPEND);
	if (ft_strcmp(arg, "<") == 0)
		return (REDIRECTION_IN);
	if (ft_strcmp(arg, ">") == 0)
		return (REDIRECTION_OUT);
	while (typemap[i].arg != NULL)
	{
		if (ft_strcmp(arg, typemap[i].arg) == 0)
			return (typemap[i].type);
		i++;
	}
	if (arg[0] == '-' && arg[1] != '\0' && isalpha((unsigned char)arg[1]))
		return (FLAGS);
	return (WORD);
}

t_arg	*create_arg_node(t_gc *gc, const char *arg)
{
	t_arg	*node;

	node = ft_gc_malloc(gc, sizeof(t_arg));
	if (node == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	node->arg = ft_shell_strdup(gc, arg);
	if (node->arg == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	node->type = get_token_type(arg);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	add_arg_to_list(t_gc *gc, t_arg **head, const char *arg)
{
	t_arg	*new_node;
	t_arg	*current_node;

	new_node = create_arg_node(gc, arg);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current_node = *head;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	current_node->next = new_node;
	new_node->prev = current_node;
}

void	ft_argadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = *lst;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
		new->prev = last;
	}
}

// Split the input string into tokens
//DEBUG print_tokens(args_head);
t_arg	*tokenizer(t_shell *shell, char *input)
{
	size_t	i;
	char	**tokens;
	t_arg	*args_head;
	t_arg	*end_node;

	i = 0;
	if (!input)
	{
		return (tokenizer_error(shell, "Error: Input: Memory alloc\n"));
	}
	tokens = ft_split_redirections(&shell->gc, input);
	if (!tokens)
	{
		return (tokenizer_error(shell, "Error: tokens: Memory alloc\n"));
	}
	args_head = NULL;
	while (tokens[i] != NULL)
	{
		add_arg_to_list(&shell->gc, &args_head, tokens[i]);
		i++;
	}
	end_node = create_arg_node(&shell->gc, "END");
	end_node->type = END;
	ft_argadd_back(&args_head, end_node);
	return (args_head);
}

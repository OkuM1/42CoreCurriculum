/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:58:44 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/24 13:24:26 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig;

char	*get_input(t_shell *shell)
{
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	if (ft_quotes_not_closed(line))
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	if (ft_quotes_not_closed(line))
	{
		shell->exit_status = 2;
		free(line);
		return (NULL);
	}
	return (line);
}

// Function to check if piping is needed
int	needs_piping(t_command *cmds_head)
{
	t_command	*current_cmd;

	current_cmd = cmds_head;
	while (current_cmd)
	{
		if (current_cmd->next)
		{
			return (1);
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}

// Main loop for shell
//print_commands(shell->cmds_head);
static int	prepare_execution(t_shell *shell, char **expanded_vars)
{
	char	*input;

	input = get_input(shell);
	if (!input)
	{
		return (0);
	}
	*expanded_vars = expand_string(shell, input, shell->exit_status);
	shell->args_head = tokenizer(shell, *expanded_vars);
	if (syntax_checker(shell->args_head) == 1)
	{
		exit_status_and_free(shell, *expanded_vars, 2);
		free(input);
		return (0);
	}
	shell->cmds_head = create_and_populate_commands
		(shell, &shell->gc, shell->args_head);
	if (!shell->cmds_head)
	{
		exit_status_and_free(shell, *expanded_vars, 1);
		free(input);
		return (0);
	}
	free(input);
	return (1);
}

void	execute_shell(t_shell *shell)
{
	char	*expanded_vars;

	while (1)
	{
		handle_signals("interactive");
		if (prepare_execution(shell, &expanded_vars) == 0)
			continue ;
		if (g_sig != SIGINT)
			execute_shell_is_piping_needed(shell);
	}
}

// Main shell execution loop
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	execute_shell(&shell);
	ft_gc_free(&shell.gc);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:16:07 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 11:25:57 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**init_env(char **envp, t_gc *gc)
{
	char	**env_copy;
	int		env_len;
	int		i;

	env_len = ft_env_len(envp);
	env_copy = (char **)ft_gc_malloc(gc, sizeof(char *) * (env_len + 1));
	if (!env_copy)
	{
		perror("Failed to allocate memory for environment copy");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < env_len)
	{
		env_copy[i] = ft_shell_strdup(gc, envp[i]);
		i++;
	}
	env_copy[env_len] = NULL;
	return (env_copy);
}

void	init_shell(t_shell *shell, char **envp)
{
	ft_gc_init(&shell->gc, shell);
	shell->env = init_env(envp, &shell->gc);
	shell->cmds_head = NULL;
	shell->exit_status = 0;
	update_shlvl(shell);
}

void	set_sig_exit(t_shell *shell, int sig)
{
	if (sig == SIGINT)
	{
		shell->exit_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		shell->exit_status = 131;
	}
}

void	execute_shell_is_piping_needed(t_shell *shell)
{
	handle_signals("NONO_SIGNALO");
	if (needs_piping(shell->cmds_head))
		shell->exit_status = execute_commands_with_pipes
			(shell, shell->cmds_head);
	else
		shell->exit_status = execute_command_without_pipes
			(shell, shell->cmds_head);
	if (g_sig != 0)
		set_sig_exit(shell, g_sig);
}

//free(line);
void	exit_status_and_free(t_shell *shell, char *line, int status)
{
	(void)line;
	if (shell->exit_status == 130)
		status = 130;
	shell->exit_status = status;
}

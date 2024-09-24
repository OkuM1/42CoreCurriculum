/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:00:16 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 13:21:52 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	re_prompt(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

void	child_sigint(int sig)
{
	write(STDERR_FILENO, "\n", 1);
	g_sig = SIGINT;
	(void) sig;
}

void	quit_child(int sig)
{
	write(STDERR_FILENO, "Quit\n", 5);
	g_sig = SIGQUIT;
	(void) sig;
}

void	heredoc_sigint(int sig)
{
	g_sig = SIGINT;
	write(STDERR_FILENO, "\n", 1);
	exit(130);
	(void) sig;
}

void	handle_signals(char *mode)
{
	g_sig = 0;
	if (ft_strcmp(mode, "NONO_SIGNALO") == 0)
	{
		signal(SIGINT, child_sigint);
		signal(SIGQUIT, quit_child);
	}
	else if (ft_strcmp(mode, "interactive") == 0)
	{
		signal(SIGINT, re_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (ft_strcmp(mode, "heredoc") == 0)
	{
		signal(SIGINT, heredoc_sigint);
	}
}

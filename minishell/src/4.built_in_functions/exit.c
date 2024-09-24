/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:21:56 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/20 20:29:49 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_number(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	exiting_with(t_shell *shell, int code)
{
	if (ft_atoi(ft_getenv(shell, "SHLVL")) == shell->origin_lvl)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_gc_free(&shell->gc);
		exit(code);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(code);
}

int	handle_exit_args(t_shell *shell, char **args)
{
	int		code;
	char	*cleaned_arg;

	cleaned_arg = strip_quotes(&shell->gc, args[0]);
	if (!cleaned_arg)
		return (1);
	if (!is_number(cleaned_arg))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exiting_with(shell, 2);
		return (2);
	}
	code = (ft_atoi(cleaned_arg) % 256 + 256) % 256;
	if (args[1])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exiting_with(shell, code);
	return (code);
}

int	built_in_exit(t_shell *shell)
{
	t_command	*cmd;
	char		**args;

	cmd = shell->cmds_head;
	if (!cmd || !(cmd->args))
		exiting_with(shell, 0);
	args = cmd->args;
	return (handle_exit_args(shell, args));
}

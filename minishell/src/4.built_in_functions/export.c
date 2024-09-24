/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:27:20 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:46:00 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Export built-in command
int	handle_invalid_export(int has_errors)
{
	(void)has_errors;
	ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
	return (1);
}

int	equal_sign_found(t_shell *shell, char *arg, int has_errors, t_gc *gc)
{
	char	*var_name;

	if (arg[0] == '=' || arg[ft_strlen(arg) - 1] == '=')
	{
		has_errors = handle_invalid_export(has_errors);
		return (has_errors);
	}
	else
	{
		var_name = find_variable(gc, arg);
		if (is_valid_identifier(var_name))
			shell->env = change_or_add_env_var(gc, arg, shell->env);
		else
			has_errors = handle_invalid_export(has_errors);
	}
	return (has_errors);
}

int	equal_sign_not_found(t_shell *shell, char *arg, int has_errors, t_gc *gc)
{
	char	*export_arg;

	if (is_valid_identifier(arg))
	{
		export_arg = ft_shell_strjoin(gc, arg, "=");
		export_arg = ft_shell_strjoin(gc, export_arg, "");
		shell->env = change_or_add_env_var(gc, export_arg, shell->env);
	}
	else
		has_errors = handle_invalid_export(has_errors);
	return (has_errors);
}

int	export_loop(t_shell *shell, char **args)
{
	int		i;
	int		has_errors;
	char	*arg;
	t_gc	*gc;

	gc = &shell->gc;
	has_errors = 0;
	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (arg && ft_strchr(arg, '='))
			has_errors = equal_sign_found(shell, arg, has_errors, gc);
		else
			has_errors = equal_sign_not_found(shell, arg, has_errors, gc);
		i++;
	}
	return (has_errors);
}

int	built_in_export(t_shell *shell)
{
	char	**args;
	int		has_errors;

	has_errors = 0;
	args = shell->cmds_head->args;
	if (!args || !args[0])
	{
		print_export_env(&shell->gc, shell->env);
		return (0);
	}
	has_errors = export_loop(shell, args);
	return (has_errors);
}

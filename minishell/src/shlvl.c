/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:54:25 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/20 18:27:44 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;
	char	*shlvl_env_var;

	shlvl_str = ft_getenv(shell, "SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	new_shlvl = ft_itoa(shlvl);
	shell->origin_lvl = shlvl;
	shlvl_env_var = ft_shell_strjoin(&shell->gc, "SHLVL=", new_shlvl);
	shell->env = change_or_add_env_var(&shell->gc, shlvl_env_var, shell->env);
	free(new_shlvl);
}

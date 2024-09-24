/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:20:34 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/21 18:47:42 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_shell_strdup(t_gc *gc, const char *s1)
{
	char	*dest;
	size_t	i;

	dest = (char *) ft_gc_malloc(gc, ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_shell_strndup(t_gc *gc, const char *s1, size_t n)
{
	char	*dest;
	size_t	i;

	dest = (char *) ft_gc_malloc(gc, (n + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

//null protection
char	*ft_shell_strjoin(t_gc *gc, char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newstr = (char *) ft_gc_malloc(gc, (ft_strlen(s1)
				+ ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (s1[i])
		newstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		newstr[j++] = s2[i++];
	newstr[j] = '\0';
	return (newstr);
}

// Helper function to extract a substring from a string
char	*ft_shell_substr(t_gc *gc, char const *s,
unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_shell_strdup(gc, ""));
	sub = (char *)ft_gc_malloc(gc, (sizeof(char) * (len + 1)));
	if (!(sub))
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

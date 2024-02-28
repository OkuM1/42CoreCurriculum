/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:23:45 by mokutucu          #+#    #+#             */
/*   Updated: 2023/11/17 20:07:07 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*newstr;
	size_t	s1_len;
	int		start;
	int		end;

	start = 0;
	s1_len = ft_strlen(s1) - 1;
	end = s1_len;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
	{
		start++;
	}
	while (s1[end] != '\0' && ft_strchr(set, s1[end]))
	{
		end--;
	}
	newstr = ft_substr(s1, start, end - start + 1);
	return (newstr);
}

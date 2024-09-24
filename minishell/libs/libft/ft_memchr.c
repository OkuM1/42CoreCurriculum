/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:40:09 by mokutucu          #+#    #+#             */
/*   Updated: 2023/11/16 16:48:19 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	c1;

	str = (unsigned char *) s;
	c1 = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == c1)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}

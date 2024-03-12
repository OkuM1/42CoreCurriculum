/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:07:14 by mokutucu          #+#    #+#             */
/*   Updated: 2023/11/24 19:16:53 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp_src;
	char	*tmp_dest;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	tmp_src = (char *) src;
	tmp_dest = (char *) dst;
	i = 0;
	if (tmp_dest > tmp_src)
	{
		while (len-- > 0)
		{
			tmp_dest[len] = tmp_src[len];
		}
	}
	else
	{
		while (i < len)
		{
			tmp_dest[i] = tmp_src[i];
			i++;
		}
	}
	return (dst);
}

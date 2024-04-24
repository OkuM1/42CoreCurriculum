/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:29:20 by mokutucu          #+#    #+#             */
/*   Updated: 2023/11/22 15:38:00 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_size(int n)
{
	long int	length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		length += 1;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char		*res;
	long int	num;
	long int	length;

	length = ft_size(n);
	num = n;
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	if (num == 0)
		res[0] = '0';
	res[length] = '\0';
	while (num != 0)
	{
		res[length - 1] = (num % 10) + '0';
		length--;
		num /= 10;
	}
	return (res);
}

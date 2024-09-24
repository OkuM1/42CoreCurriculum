/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:01:53 by mokutucu          #+#    #+#             */
/*   Updated: 2024/03/12 15:17:47 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_ptr(long nbr)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (nbr < 0)
	{
		write(1, "-", 1);
		return (print_ptr(-nbr) + 1);
	}
	else if (nbr < 16)
		return (print_char(symbols[nbr]));
	else
	{
		count = print_ptr(nbr / 16);
		return (count + print_ptr(nbr % 16));
	}
}

int	print_pointer(va_list ap)
{
	unsigned long long int	num;
	int						count;

	count = 0;
	num = va_arg(ap, unsigned long long int);
	if (num == 0)
		count += print_str("(nil)");
	else
	{
		count += print_str("0x");
		count += print_ptr(num);
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:54:16 by mokutucu          #+#    #+#             */
/*   Updated: 2024/02/27 15:01:05 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);

int		print_format(char sign, va_list args);

int		print_char(int c);

int		print_str(char *str);

int		print_digit(long nbr, int base, int yesoryes);

int		print_unsigned(unsigned int num);

int		print_ptr(unsigned long long nbr);

int		print_pointer(va_list ap);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgarh <olgarh@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 16:12:25 by olgarh            #+#    #+#             */
/*   Updated: 2026/11/23 18:07:50 by olgarh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_checks(va_list inputs, const char c, int *count)
{
	if (c == 's')
		ft_print_string(va_arg(inputs, char *), count);
	else if (c == 'c')
		ft_print_char(va_arg(inputs, int), count);
	else if (c == 'd' || c == 'i')
		ft_print_number(va_arg(inputs, int), count);
	else if (c == 'x' || c == 'X' || c == 'u')
		ft_print_by_base(va_arg(inputs, unsigned int), c, count);
	else if (c == 'p')
		ft_print_pointer(va_arg(inputs, unsigned long), count);
	else if (c == '%')
	{
		write(1, "%", 1);
		*count = *count + 1;
	}
	else
		return (0);
	return (*count);
}

int	ft_printf(const char *s, ...)
{
	va_list	inputs;
	int		count;

	va_start(inputs, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (ft_checks(inputs, *(s + 1), &count) == -1)
				return (va_end(inputs), count);
			s = s + 2;
			continue ;
		}
		if (*s == '\0')
			break ;
		count++;
		if (write(1, s, 1) == -1)
			return (va_end(inputs), -1);
		s++;
	}
	return (va_end(inputs), count);
}

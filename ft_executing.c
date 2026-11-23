/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgarh <olgarh@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 22:21:23 by olgarh            #+#    #+#             */
/*   Updated: 2026/11/23 18:30:03 by olgarh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		if (write(1, s, 1) == -1)
		{
			*count = -1;
			return (*count);
		}
		s++;
		*count = *count + 1;
	}
	return (*count);
}

int	ft_print_char(char s, int *count)
{
	if (write(1, &s, 1) == -1)
	{
		*count = -1;
		return (*count);
	}
	*count = *count + 1;
	return (*count);
}

int	ft_print_number(int nb, int *count)
{
	long	n;
	char	mod;

	n = nb;
	if (nb < 0)
	{
		if (write(1, "-", 1) == -1)
		{
			*count = -1;
			return (*count);
		}
		n = -n;
		*count = *count + 1;
	}
	if (n > 9)
		ft_print_number(n / 10, count);
	mod = n % 10 + '0';
	if (write(1, &mod, 1) == -1)
	{
		*count = -1;
		return (*count);
	}
	*count = *count + 1;
	return (*count);
}

int	ft_print_by_base(unsigned long nb, const char c, int *count)
{
	char			*base;
	unsigned int	len;

	if (c == 'X')
		base = "0123456789ABCDEF";
	else if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789";
	len = ft_strlen(base);
	if (nb >= len)
		ft_print_by_base(nb / len, c, count);
	if (write(1, &base[(nb % len)], 1) == -1)
	{
		*count = -1;
		return (*count);
	}
	*count = *count + 1;
	return (*count);
}

int	ft_print_pointer(unsigned long nb, int *count)
{
	if (!nb)
	{
		if (write(1, "(nil)", 5) == -1)
		{
			*count = -1;
			return (*count);
		}
		*count += 5;
		return (*count);
	}
	if (write(1, "0x", 2) == -1)
	{
		*count = -1;
		return (*count);
	}
	*count += 2;
	ft_print_by_base(nb, 'x', count);
	return (*count);
}

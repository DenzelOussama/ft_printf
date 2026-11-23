/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgarh <olgarh@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 16:12:13 by olgarh            #+#    #+#             */
/*   Updated: 2026/11/23 16:12:48 by olgarh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_strlen(const char *c)
{
	unsigned int	result;

	result = 0;
	while (c[result])
		result++;
	return (result);
}

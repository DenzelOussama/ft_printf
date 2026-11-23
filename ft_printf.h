/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olgarh <olgarh@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 16:12:32 by olgarh            #+#    #+#             */
/*   Updated: 2026/11/23 16:12:33 by olgarh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINT_H
# define LIBFTPRINT_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int				ft_printf(const char *format, ...);
int				ft_checks(va_list inputs, const char c, int *count);
int				ft_print_string(char *s, int *count);
int				ft_print_char(char s, int *count);
int				ft_print_number(int nb, int *count);
int				ft_print_by_base(unsigned long nb, char c, int *count);
unsigned int	ft_strlen(const char *c);
int				ft_print_pointer(unsigned long, int *count);

#endif
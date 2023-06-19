/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:05:21 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:29:21 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle(char c, va_list args, int fd)
{
	if (c == 'i' || c == 'd')
		return (ft_putnbr_fd(fd, va_arg(args, int)));
	if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	if (c == 'c')
		return (ft_putchar_fd(fd, va_arg(args, int)));
	if (c == 'p')
		return (ft_putptr_fd(fd, va_arg(args, void *)));
	if (c == 'u')
		return (ft_putnbr_fd(fd, va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_putlhex_fd(fd, va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_putuhex_fd(fd, va_arg(args, unsigned int)));
	if (c == '%')
		return (ft_putchar_fd(fd, '%'));
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	va_start(args, format);
	printed_chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			printed_chars += ft_handle(*(++format), args, fd);
			if (!(*format))
				break ;
		}
		else
			printed_chars += ft_putchar_fd(*format, fd);
		format++;
	}
	va_end(args);
	return (printed_chars);
}

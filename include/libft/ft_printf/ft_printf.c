/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <<marvin@42.fr>>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:53:49 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/22 11:29:43 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_check(char s, va_list *current, int *len)
{
	if (s == 's')
		ft_put_str_len(va_arg(*current, char *), len);
	else if (s == 'd' || s == 'i')
		ft_putnbr_len(va_arg(*current, int), len);
	else if (s == 'c')
		ft_putchar_len(va_arg(*current, int), len);
	else if (s == 'p')
		ft_putvoid(va_arg(*current, void *), len);
	else if (s == 'u')
		ft_unsigned_len(va_arg(*current, unsigned int), len);
	else if (s == 'x')
		ft_put_hex_lowercase_len(va_arg(*current, unsigned int), len);
	else if (s == 'X')
		ft_put_hex_uppercase_len(va_arg(*current, unsigned int), len);
	else if (s == '%')
		ft_putchar_len('%', len);
}

int	ft_printf(const char *str, ...)
{
	va_list	current;
	int		i;
	int		len;

	if (!str)
		return (0);
	i = 0;
	len = 0;
	va_start(current, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			ft_printf_check(str[i], &current, &len);
		}
		else
			ft_putchar_len((char)str[i], &len);
		i++;
	}
	va_end(current);
	return (len);
}

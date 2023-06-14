/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:57:44 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/22 17:59:23 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_hexa2(unsigned long long int n, char *base, int *len)
{
	if (n > 15)
	{
		ft_putnbr_hexa2(n / 16, base, len);
	}
	ft_putchar_len(base[n % 16], len);
}

void	ft_putvoid(void *ptr, int *len)
{
	unsigned long long int	i;

	if (!ptr)
	{
		write (1, "(nil)", 5);
		*len = *len + 5;
	}
	else
	{
		i = (unsigned long long int) ptr;
		ft_putchar_len('0', len);
		ft_putchar_len('x', len);
		ft_putnbr_hexa2(i, "0123456789abcdef", len);
	}
}

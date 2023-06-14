/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:38:24 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/22 11:45:53 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_len(int n, int *len)
{
	unsigned int	c;

	if (n < 0)
	{
		ft_putchar_len('-', len);
		c = n * -1;
	}
	else
		c = n;
	if (c > 9)
	{
		ft_putnbr_len(c / 10, len);
		ft_putnbr_len(c % 10, len);
	}
	else
		ft_putchar_len((c + '0'), len);
}

void	ft_put_nbr_unsigned_len(unsigned int nbr, int *len)
{
	if (nbr > 9)
	{
		ft_put_nbr_unsigned_len((nbr / 10), len);
		ft_put_nbr_unsigned_len((nbr % 10), len);
	}
	else
		ft_putchar_len((nbr + '0'), len);
}

void	ft_unsigned_len(unsigned int c, int *len)
{
	ft_put_nbr_unsigned_len(c, len);
}

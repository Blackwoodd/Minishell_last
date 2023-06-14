/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:46:42 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/22 15:21:14 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_base_len(unsigned int nbr, const char *base, int *length)
{
	int		len;
	char	c;

	len = ft_strlen((char *)base);
	c = base[nbr % len];
	nbr = nbr / len;
	if (nbr > 0)
	{
		ft_put_base_len(nbr, base, length);
	}
	ft_putchar_len(c, length);
}

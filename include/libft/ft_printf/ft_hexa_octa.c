/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_octa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:29:43 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/22 13:51:24 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_hex_lowercase_len(unsigned int c, int *len)
{
	ft_put_base_len(c, "0123456789abcdef", len);
}

void	ft_put_hex_uppercase_len(unsigned int c, int *len)
{
	ft_put_base_len(c, "0123456789ABCDEF", len);
}

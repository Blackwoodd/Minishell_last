/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <<marvin@42.fr>>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:05:07 by nsalhi            #+#    #+#             */
/*   Updated: 2022/10/18 11:17:04 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*str;

	i = 0;
	a = (unsigned char)c;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = a;
		i++;
	}
	return (b);
}

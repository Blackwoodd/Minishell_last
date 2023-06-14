/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:30:50 by nassm             #+#    #+#             */
/*   Updated: 2023/06/07 14:45:35 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexnbrlen(unsigned long long nbr)
{
	int	count;

	if (nbr == 0)
		return (1);
	count = 0;
	while (nbr != 0)
	{
		nbr /= 16;
		count++;
	}
	return (count);
}

static char	*ft_convert(unsigned long long dec, int uppcase, char *ptr)
{
	int	r;

	*(--ptr) = '\0';
	if (dec == 0)
		*(--ptr) = '0';
	while (dec != 0)
	{
		ptr--;
		r = dec % 16;
		if (r < 10)
			r += '0';
		else
		{
			if (uppcase == 0)
				r += 'W';
			else
				r += '7';
		}
		*ptr = r;
		dec /= 16;
	}
	return (ptr);
}

char	*ft_htoa(unsigned long long dec, int uppcase)
{
	char	*hexnum;
	char	*ptr;
	int		nbrlen;

	nbrlen = ft_hexnbrlen(dec);
	hexnum = malloc((nbrlen + 1) * sizeof(*hexnum));
	if (hexnum == NULL)
		return (NULL);
	ptr = hexnum + nbrlen + 1;
	return (ft_convert(dec, uppcase, ptr));
}
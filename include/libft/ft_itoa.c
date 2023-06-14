/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:00:40 by nsalhi            #+#    #+#             */
/*   Updated: 2023/02/20 15:27:38 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_digit(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int c)
{
	char		*str_num;
	int			i;
	int			count;
	long int	x;

	i = 0;
	x = (long int)c;
	count = ft_get_digit(c);
		str_num = (char *)malloc((count + 1) * sizeof(char));
	if (!str_num)
		return (NULL);
	if (x < 0)
	{
		str_num[0] = '-';
		x *= -1;
		i++;
	}
	str_num[count] = '\0';
	while (count-- > i)
	{
		str_num[count] = (x % 10) + '0';
		x /= 10;
	}
	return (str_num);
}

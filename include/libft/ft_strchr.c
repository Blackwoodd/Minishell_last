/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <<marvin@42.fr>>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:39:03 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/11 14:02:25 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		x;

	str = (char *)s;
	x = ft_strlen(s) + 1;
	while (x-- > 0)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	return (NULL);
}

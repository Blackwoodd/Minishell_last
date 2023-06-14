/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <<marvin@42.fr>>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:44:45 by nsalhi            #+#    #+#             */
/*   Updated: 2022/10/18 11:21:30 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*new_dest;
	unsigned char	*new_src;
	unsigned char	find;
	size_t			i;

	if (!s || !src)
		return (NULL);
	new_dest = (unsigned char *)dest;
	new_src = (unsigned char *)src;
	find = c;
	i = 0;
	while (i < n && new_src[i] != find)
	{
		new_dest[i] = new_src[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		new_dest[i] = new_src[i];
		i++;
		return (&new_dest[i]);
	}
}	

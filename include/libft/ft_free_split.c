/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:19:43 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:26:06 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		ft_free_str(&split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

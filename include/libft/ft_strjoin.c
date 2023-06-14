/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:10:41 by nsalhi            #+#    #+#             */
/*   Updated: 2023/02/20 17:24:54 by nassimsalhi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_aux(char const *s1, char const *s2)
{
	char	*copy;
	int		i;
	int		j;

	copy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		copy[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		copy[j] = s2[i];
		j++;
		i++;
	}
	copy[j] = '\0';
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (NULL);
	return (ft_strjoin_aux(s1, s2));
}

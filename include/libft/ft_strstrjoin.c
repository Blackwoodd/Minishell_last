/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:07:34 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:26:51 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will append s2 to s1
will do nothing if s1 is NULL
it will ad the divider string between the strings
will free s1
*/
char	*ft_strstrjoin(char *s1, char *s2, char *divider)
{
	char	*out;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	s1 = ft_append(&s1, divider);
	out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == NULL)
		return (0);
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		out[i++] = s2[j++];
	out[i] = '\0';
	ft_free_str(&s1);
	return (out);
}

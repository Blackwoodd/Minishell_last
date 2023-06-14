/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:25:29 by nassm             #+#    #+#             */
/*   Updated: 2023/05/26 15:26:39 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
this function is similar to realloc, but only for strings
++ instead of malloc this uses calloc
-- it will create a new adress and free the old one of str
if allocation of the new size fails str will be freed
str: adress of the string you want to realloc
size: number of elements you want to realloc
new: adress of the reallocated string
*/
char	*ft_realloc_str(char *str, int size)
{
	char	*new;
	int		i;

	if (str == NULL)
		return (NULL);
	new = ft_calloc(size + 1, sizeof(*new));
	if (new == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str && str[i] && size--)
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}

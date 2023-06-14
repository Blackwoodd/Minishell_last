/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:14:48 by nassm             #+#    #+#             */
/*   Updated: 2023/05/30 16:14:51 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arr_realloc(char *array[], size_t size)
{
	char	**reallocated;
	int		i;

	reallocated = ft_calloc(size + 1, sizeof(*reallocated));
	if (reallocated == NULL)
		return (NULL);
	i = 0;
	while (size-- && array && array[i])
	{
		reallocated[i] = ft_strdup(array[i]);
		i++;
	}
	ft_free_str_array(&array);
	return (reallocated);
}

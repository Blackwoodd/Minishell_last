/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:34:19 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:30:51 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
add a new str to a prexisting tab ((*arr)[pos])
*/
char	**ft_add_str_to_tab(char ***arr, int pos, char *new)
{
	int		i;

	pos++;
	if (new == NULL)
	{
		ft_free_str_array(arr);
		return (NULL);
	}
	*arr = ft_realloc_str_arr(*arr, ft_str_arr_len(*arr) + 1);
	if (*arr == NULL)
		return (NULL);
	i = ft_str_arr_len(*arr);
	while (i > pos)
	{
		(*arr)[i] = (*arr)[i - 1];
		i--;
	}
	(*arr)[i] = ft_strdup(new);
	if ((*arr)[i] == NULL)
	{
		ft_free_str_array(arr);
		return (NULL);
	}
	return (*arr);
}

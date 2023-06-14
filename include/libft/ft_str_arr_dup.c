/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:52:37 by nassm             #+#    #+#             */
/*   Updated: 2023/05/29 15:52:40 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strdup for string arrays
arr: the array to copy
cpy: the copied array that gets returned
*/
char	**ft_str_arr_dup(char **arr)
{
	char	**cpy;
	int		i;

	if (arr == NULL)
		return (NULL);
	cpy = ft_calloc(ft_str_arr_len(arr) + 1, sizeof(*cpy));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	return (cpy);
}

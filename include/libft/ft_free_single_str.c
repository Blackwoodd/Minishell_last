/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_single_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:25:57 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:30:58 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will free a single string out of a given array
will move the following strings to fill the gap
will reallocate the array to the correct size
*/
void	ft_free_single_str(char ***arr, int i)
{
	if (*arr != NULL)
		ft_free_str(&(*arr)[i++]);
	while (*arr != NULL && (*arr)[i] != NULL)
	{
		(*arr)[i - 1] = (*arr)[i];
		i++;
	}
	(*arr)[--i] = NULL;
	if (*arr != NULL && (*arr)[i] == NULL)
		*arr = ft_realloc_str_arr(*arr, i + 1);
}

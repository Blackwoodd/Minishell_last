/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:56:29 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:32:50 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will measure the length of str until first occurance of c or end of string
*/
int	ft_strclen(char *str, char c)
{
	int	len;

	len = 0;
	while (str && str[len] && str[len] != c)
		len++;
	return (len);
}

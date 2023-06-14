/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_len_div.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:35:45 by nassm             #+#    #+#             */
/*   Updated: 2023/05/27 12:46:05 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will append len bytes of src to dst and free the old dst
dst will be divided from src by div
if dst/src == NULL or strlen(src)<len it returns NULL
if a malloc-error happens it will free dst and return NULL
*/
char	*ft_append_len_div(char **dst, char *src, int len, char *div)
{
	int		i;
	int		j;
	char	*out;

	j = 0;
	if (*dst == NULL || src == NULL || (int)ft_strlen(src) < len)
		return (NULL);
	out = ft_append(dst, div);
	if (out == NULL)
		return (NULL);
	i = ft_strlen(out);
	out = ft_realloc_str(out, i + len + 1);
	while (src[j] && j < len)
	{
		out[i] = src[j];
		i++;
		j++;
	}
	ft_free_str(dst);
	return (out);
}
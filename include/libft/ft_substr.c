/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <<marvin@42.fr>>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:45:52 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/12 11:09:19 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	lentotal;

	if (str == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(str) < start)
		return (ft_strdup(""));
	lentotal = ft_strlen(str + start);
	if (lentotal < len)
		len = lentotal;
	substr = (char *)malloc((sizeof(char) * (len + 1)));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, str + start, len + 1);
	return (substr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:43:27 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:26:32 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putlnbr_fd(int fd, long nbr)
{
	int		printed_chars;
	char	*s;

	s = ft_itoa(nbr);
	if (s == NULL)
		return (0);
	printed_chars = ft_putstr_fd(s, fd);
	free(s);
	s = NULL;
	return (printed_chars);
}

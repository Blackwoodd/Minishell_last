/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuhex_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:13:04 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:25:54 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putuhex_fd(int fd, unsigned long long nbr)
{
	char	*hex;
	int		printed_chars;

	hex = ft_htoa(nbr, 1);
	if (hex == NULL)
		return (0);
	printed_chars = ft_putstr_fd(hex, fd);
	free(hex);
	return (printed_chars);
}

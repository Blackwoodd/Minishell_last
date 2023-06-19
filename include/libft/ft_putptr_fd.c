/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:15:13 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:31:17 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(int fd, void *ptr)
{
	return (ft_putstr_fd("0x", fd) + \
	ft_putlhex_fd(fd, (unsigned long long)ptr));
}

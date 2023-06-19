/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:25:33 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 16:29:43 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
    use perror for the message and return the exit status
*/
int	ft_perror(int exit_status, char *msg)
{
	perror(msg);
	return (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:25:33 by nassm             #+#    #+#             */
/*   Updated: 2023/06/01 10:26:21 by nassm            ###   ########.fr       */
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
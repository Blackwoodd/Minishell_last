/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:37:23 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 14:44:36 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printf_exit2(void)
{
	printf ("exit\n");
	printf ("bash: exit: too many arguments\n");
	return ;
}

void	printf_exit(char *arg)
{
	printf ("exit\n");
	printf ("bash: exit: %s: numeric argument required\n", arg);
	exit (0);
}

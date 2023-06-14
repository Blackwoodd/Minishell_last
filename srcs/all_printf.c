/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:37:23 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/31 10:58:25 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printf_exit2(void)
{
	printf ("bash: exit: too many arguments\n");
	return ;
}

void	printf_exit(char *arg)
{
	printf ("bash: exit: %s: numeric argument required\n", arg);
	exit (0);
}

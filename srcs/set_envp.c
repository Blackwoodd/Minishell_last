/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:14:50 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 16:46:38 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is used to manage a static variable static_envp that holds
	the environment variables.
*/
//if ERROR DERNIER CHANGEMENT ==> static char	**static_envp = NULL;

static char	**core_get_envp(char **envp, bool reset)
{
	static char	**static_envp;

	static_envp = NULL;
	if (envp == NULL && !reset)
		return (static_envp);
	if (reset)
	{
		static_envp = NULL;
		return (NULL);
	}
	static_envp = envp;
	return (static_envp);
}

void	set_envp(char **envp)
{
	core_get_envp(envp, false);
}

char	**get_envp(void)
{
	return (core_get_envp(NULL, false));
}

void	reset_envp(void)
{
	core_get_envp(NULL, true);
}

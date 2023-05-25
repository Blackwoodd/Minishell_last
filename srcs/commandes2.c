/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:28 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 14:48:53 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	commande_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf ("%s\n", env[i]);
		i++;
	}
}

void	commande_export(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf ("declare -x ");
		printf ("%s\n", env[i]);
		i++;
	}
}

void	commande_unset(char **env, char *word)
{
	int	j;
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (env[i] != NULL)
	{
		if (compare(env[i], word) == 0)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found)
	{
		j = i;
		while (env[j] != NULL)
		{
			env[j] = env[j + 1];
			j++;
		}
	}
}

void	commande_exit(char *seconde)
{
	int	i;

	i = 0;
	if (!seconde)
	{	
		printf ("exit\n");
		exit (0);
	}
	while (seconde[i])
	{
		if (seconde[i] == ' ')
		{	
			printf_exit2();
			return ;
		}
		if (seconde[i] < '0' || seconde[i] > '9')
			printf_exit(seconde);
		if ((seconde[i] >= 'a' && seconde[i] >= 'z')
			|| (seconde[i] >= 'A' && seconde[i] >= 'Z'))
			printf_exit(seconde);
		if (i >= 20)
			printf_exit(seconde);
		i++;
	}
	printf ("exit\n");
	exit (0);
}

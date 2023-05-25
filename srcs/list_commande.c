/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commande.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:35:03 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 16:35:17 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	list_of_command(char *first, char *seconde, char **env)
{
	if (compare(first, ECHO) == 0 || compare(first, ECHO_N) == 0)
	{
		if (seconde == NULL)
			printf ("\n");
		commande_echo(first, seconde);
	}
	else if (compare(first, CD) == 0)
	{
		if (!seconde)
			exit (0);
		commande_cd(seconde);
	}
	else if (compare(first, ENV) == 0)
	{
		if (seconde)
			exit (0);
		commande_env(env);
	}
	else if (compare(first, EXIT) == 0)
		commande_exit(seconde);
	else if (compare(first, PWD) == 0)
		commande_pwd();
	else if (compare(first, EXPORT) == 0)
		commande_export(env);
	else if (compare(first, UNSET) == 0)
		commande_unset(env, seconde);
	else
		printf ("bash: %s: command not found\n", first);
	free (first);
	free (seconde);
}
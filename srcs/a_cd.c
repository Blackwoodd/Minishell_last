/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:32 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/19 15:32:57 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commande_cd(char **word)
{
	char	cwd[1000];

	if (word[2] != NULL)
	{
		printf ("cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (chdir(word[1]) != 0)
	{
		if (word[1] == NULL)
		{
			chdir("..");
			return (EXIT_SUCCESS);
		}
		if (word[1][0] == '-' && !word[1][1])
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				printf("%s\n", cwd);
				return (EXIT_SUCCESS);
			}
		}
		if (word [1][0] == '-' && word[1][1] == '-' && word[1][2] == '-')
		{
			printf ("cd: --: invalid option\n");
			return (EXIT_FAILURE);
		}
		if (ft_strncmp(word[1], "Makefile", 8) == 0)
			printf("cd: Makefile: Not a directory\n");
		else
			printf("cd: %s: No such file or directory\n", word[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

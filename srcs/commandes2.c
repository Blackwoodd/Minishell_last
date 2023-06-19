/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:28 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/19 14:08:13 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

///////////////////// ENV ////////////////////////

int	commande_env(char **tab)
{
	int		i;
	t_env	*envar;

	envar = get_envar();
	if (envar == NULL || envar->env_var == NULL)
		return (EXIT_FAILURE);
	if (tab != NULL && tab[1] != NULL)
	{
		if (access(tab[1], F_OK) == 0)
		{
			ft_fprintf(STDERR_FILENO, "env: %s: Permission denied\n", tab[1]);
			return (126);
		}
		ft_fprintf(2, "env: %s: No such file or directory\n", tab[1]);
		return (127);
	}
	i = 0;
	while (envar->env_var && envar->env_var[i] != NULL)
	{
		if (ft_printf("%s\n", envar->env_var[i++]) == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

///////////////////// EXPORT ////////////////////////

int	commande_export(char **tab)
{
	int		i;
	t_env	*envar;

	i = 0;
	envar = get_envar();
	if (envar == NULL || envar->env_var == NULL)
		return (EXIT_FAILURE);
	if (tab[1] != NULL && tab[1][0] == '-')
		return (EXIT_FAILURE);
	while (envar->env_var && envar->env_var[i] != NULL)
	{
		if (ft_printf("export %s\n", envar->env_var[i++]) == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:34:20 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/19 15:34:31 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
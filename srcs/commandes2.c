/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:14:28 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/14 16:54:20 by nbechon          ###   ########.fr       */
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

/////////// EXIT ///////////////

static bool	valid_exit(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab && tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (ft_issign(tab[i][j]))
				j++;
			if (!ft_isdigit(tab[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	commande_exit(char **tab)
{
	long	exit_code;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (ft_strncmp(tab[i], "exit", ft_strlen(tab[i])) != 0)
		return (EXIT_FAILURE);
	i++;
	if (tab[i])
		exit_code = ft_atol(tab[i]);
	else
		exit_code = get_err_code();
	if (!valid_exit(tab + i) || ft_strlen(tab[i]) > 19)
	{
		if (tab[2] != NULL)
		{
			while (tab[2][j])
			{
				if (tab[2][j] < '0' || tab[2][j] > '9')
				{
					ft_fprintf(STDERR_FILENO, "exit\n");
					ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
					return (EXIT_FAILURE);
				}
				j++;
			}
		}
		ft_fprintf(STDERR_FILENO, "exit\n");
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			tab[1]);
		exit_code = 255;
	}
	else if (tab[i] && tab[++i])
	{
		ft_fprintf(STDERR_FILENO, "exit\n");
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else
		ft_fprintf(STDERR_FILENO, "exit\n");
	exit(exit_code);
	return (exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:16:05 by nbechon           #+#    #+#             */
/*   Updated: 2023/07/12 15:30:57 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_get_var(t_env *envar, int i)
{
	char	**split;
	char	*var;

	split = ft_split(envar->env_var[i], '=');
	if (split == NULL)
		return (NULL);
	var = ft_strdup(split[0]);
	ft_free_str_array(&split);
	return (var);
}

static void	ft_suppr_var(t_env *envar, int i)
{
	int	j;

	ft_free_str(&envar->env_var[i]);
	j = i;
	while (envar->env_var[j + 1])
	{
		envar->env_var[j] = envar->env_var[j + 1];
		j++;
		if (envar->env_var[j + 1] == NULL)
			envar->env_var[j] = NULL;
		i = ft_str_arr_len(envar->env_var);
	}
}

static int	norm_unset(char **tab, t_env *envar, int i, int j)
{
	char	*var;

	var = NULL;
	if (ft_strcmp(envar->env_var[i], tab[j]) == 0
		|| ft_strcmp(envar->env_var[i], tab[j]) == 61)
	{
		var = ft_get_var(envar, i);
		if (var == NULL)
			return (EXIT_FAILURE);
		if (ft_strncmp(var, tab[j], ft_strlen(var)) != 0
			|| ft_strncmp(var, tab[j], ft_strlen(tab[j]) != 0))
		{
			ft_free_str(&var);
			return (2);
		}
		ft_suppr_var(envar, i);
	}
	ft_free_str(&var);
	return (EXIT_SUCCESS);
}

int	verif_unset(char *tab)
{
	int	j;

	j = 0;
	if (tab[j] == '-')
		return (printf ("unset: -%c: invalid option\n", tab[j + 1]), 1);
	while (tab[j])
	{
		if (tab[j] == '_' || (tab[j] >= 'A' && tab[j] <= 'Z')
			|| (tab[j] >= 'a' && tab[j] <= 'z')
			|| (tab[j] >= '0' && tab[j] <= '9'))
			j++;
		else if (tab[j] == '!')
		{
			while (tab[j])
			{
				printf ("%c", tab[j]);
				j++;
			}
			return (printf (": event not found\n"), 1);
		}
		else
			return (printf ("export: `%s': not a valid identifier\n", tab), 0);
	}
	return (0);
}

int	commande_unset(char **tab)
{
	int	i;
	int	j;
	int	count;
	int	for_exit;
	int	out;
	t_env	*envar;

	envar = get_envar();
	if (tab[1] == NULL)
		return (EXIT_SUCCESS);
	j = 0;
	i = 0;
	if (tab[1][0] >= '0' && tab[1][0] <= '9')
	{
		printf ("export: `%s': not a valid identifier\n", tab[1]);
		return (EXIT_FAILURE);
	}
	count = 1;
	for_exit = 0;
	while (tab[count] != NULL)
	{
		if (verif_unset(tab[count]) == 1)
			return (EXIT_FAILURE);
		count++;
	}
	if (for_exit == 1)
		return (EXIT_FAILURE);
	if (tab[1] != NULL && (tab[1][0] <= '!' || tab[1][0] >= '}'))
		printf ("unset: `': not a valid identifier\n");
	j = 1;
	while (tab[j])
	{
		i = 0;
		while (envar->env_var[i])
		{
			out = norm_unset(tab, envar, i, j);
			if (out == 2)
				break ;
			else if (out == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

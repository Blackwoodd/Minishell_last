/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:07:35 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/19 15:20:11 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_no_number(char *tab)
{
	int	i;

	i = 0;
	//if (tab[0] == '-' && (tab[1] >= 0 || tab[1] <= 9))
	//	i++;
	//if (tab[0] == '+' && (tab[1] >= 0 || tab[1] <= 9))
	//	i++;
	while (tab[i])
	{
		if (tab[i] < '0' || tab[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	print_error_arg(void)
{
	ft_fprintf(STDERR_FILENO, "exit\n");
	ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
}

int	commande_exit(char **tab)
{
	long	exit_code;

	if (ft_strncmp(tab[0], "exit", ft_strlen(tab[0])) != 0)
		return (EXIT_FAILURE);
	if (tab[0])
		exit_code = ft_atol(tab[0]);
	else
		exit_code = get_err_code();
	if (tab[1] != NULL)
	{
		if (check_no_number(tab[1]) == 1 || ft_strlen(tab[1]) > 19)
		{
			ft_fprintf(STDERR_FILENO,
				"exit\nexit: %s: numeric argument required\n", tab[1]);
			exit_code = 255;
		}
		else
		{
			if (tab[2] != NULL)
				return (print_error_arg(), EXIT_FAILURE);
			ft_fprintf(STDERR_FILENO, "exit\n");
		}
	}
	else
		ft_fprintf(STDERR_FILENO, "exit\n");
	exit(exit_code);
	return (exit_code);
}

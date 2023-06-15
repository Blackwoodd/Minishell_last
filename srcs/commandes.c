/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:32 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/15 14:51:48 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	echo_help(char *word)
{
	int	i;

	i = 2;
	while (word[i])
	{
		if (word[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	commande_echo(char **word)
{
	bool	new_line;

	new_line = true;
	if (ft_strncmp(*word, "echo", ft_strlen(*word)) != 0)
		return (EXIT_FAILURE);
	word++;
	while (*word && ft_strncmp(*word, "-n", 2) == 0)
	{
		if (echo_help(*word) == true)
		{
			new_line = false;
			word++;
		}
		else
			break ;
	}
	while (*word)
	{
		write(1, *word, ft_strlen(*word));
		word++;
		if (*word != NULL)
			write (1, " ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int	commande_pwd(char **word)
{
	char	cwd[1000];
	int		i;

	i = 0;
	if (word[1] != NULL && word[1][0] == '-')
	{
		printf ("pwd: ");
		while ((word[1][i] == '-' && i < 2) || i != 2)
		{
			printf ("%c", word[1][i]);
			i++;
		}
		printf (": invalid option\n");
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("PWD");
		return (EXIT_FAILURE);
	}
}

int	commande_cd(char **word)
{
	if (chdir(word[1]) != 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

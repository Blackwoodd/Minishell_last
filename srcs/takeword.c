/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeword.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:29:55 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 16:34:37 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*take_firstword(char *input)
{
	int		i;
	int		j;
	int		len;
	int		repaire;
	char	*word;

	len = 0;
	i = 0;
	j = 0;
	while (input[i] == ' ')
		i++;
	while (input[i] != ' ')
	{
		len++;
		i++;
	}
	j = i;
	while (input[j] != '\0')
	{
		if (input[j] != ' ')
		{
			if (input[j] == '-' && input[j + 1] == 'n')
			{
				repaire = 1;
				len += 2;
			}
			break ;
		}
		j++;
	}
	word = malloc (sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (input[i] == ' ')
		i++;
	j = 0;
	while (input[i] != ' ')
	{
		word[j] = input[i];
		j++;
		i++;
	}
	if (repaire == 1)
	{
		while (input[i] != '-')
			i++;
		word[j] = ' ';
		j++;
		while (input[i] != ' ')
		{
			if (input[i] == '-' && input[i + 1] == 'n')
			{
				word[j] = '-';
				word[j + 1] = 'n';
				word[j + 2] = '\0';
				return (word);
			}
			word[j] = input[i];
			j++;
			i++;
		}
	}
	word[j] = '\0';
	return (word);
}

int	verif_nbr_word(char *input)
{
	int	i;

	i = 0;
	while ((input[i] <= 'a' && input[i] >= 'z')
		|| (input[i] <= 'A' || input[i] <= 'Z'))
		i++;
	while (input[i] != ' ' && input[i])
		i++;
	if (input[i] == '-' && input[i + 1] == 'n')
	{
		while (input[i] != ' ' && input[i])
			i++;
	}
	if (input[i] == '\0')
		return (1);
	return (0);
}

char	*take_second_word(char *input)
{
	int		i;
	int		j;
	int		len;
	int		repaire;
	char	*word;

	i = 0;
	j = 0;
	len = 0;
	if (verif_nbr_word(input) == 1)
		return (NULL);
	while (input[i] == ' ')
		i++;
	while (input[i] != ' ')
		i++;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (NULL);
	if (input[i] == '-' && input[i + 1] == 'n')
	{	
		i += 2;
		while (input[i] != ' ')
			i++;
		while (input[i] == ' ')
			i++;
	}
	repaire = i;
	while (input[i])
	{
		len++;
		i++;
	}
	word = malloc (sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	while (input[repaire])
	{
		if (input[repaire] == ' ')
		{	
			while (input[repaire] == ' ')
				repaire++;
			repaire--;
		}
		word[j] = input[repaire];
		j++;
		repaire++;
	}
	word[j] = '\0';
	return (word);
}

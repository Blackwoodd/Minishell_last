/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeword.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:29:55 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/23 16:04:34 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*take_firstword(char *input)
{
	char	*word;
	int		i;
	int		len;
	int		space;

	len = 0;
	space = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			space++;
		i++;
	}
	if (i == 0)
		exit (0);
	if (space == 0)
		len = i;
	else
		while (input[len] != ' ' || input[len + 1] == '-' || input[len] == 'n')
			len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	if (space == 0)
	{
		while (input[i])
		{
			word[i] = input[i];
			i++;
		}
	}
	else
	{
		while (input[i] != ' ' || input[i + 1] == '-')
		{
			word[i] = input[i];
			i++;
		}
	}
	word[i] = '\0';
	return (word);
}

char	*take_second_word(char *input)
{
	int		space;
	int		len;
	int		i;
	int		j;
	char	*word;

	space = 0;
	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			space++;
		i++;
	}
	if (space == 0)
		return (NULL);
	i = 0;
	while (input[i] != ' ')
		i++;
	if (input[i + 1] == '-' && input[i + 2] == 'n')
	{
		i += 3;
		if (space == 1)
			return (0);
	}
	len = i;
	while (input[len])
		len++;
	len -= i;
	word = malloc(sizeof(char) * (len));
	if (!word)
		return (NULL);
	j = 0;
	i++;
	while (input[i] != '\0')
	{
		word[j] = input[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

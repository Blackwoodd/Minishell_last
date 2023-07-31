/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:04:13 by nassm             #+#    #+#             */
/*   Updated: 2023/07/28 15:44:58 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_arr_len(char *str, char *set)
{
	char	*trimmed_str;
	int		arr_len;
	int		i;

	trimmed_str = ft_strtrim(str, set);
	if (trimmed_str == NULL)
		return (-1);
	arr_len = 0;
	i = 0;
	if (ft_strchr(set, trimmed_str[i]) == NULL)
		arr_len++;
	while (trimmed_str[i])
	{
		if (ft_strchr(set, trimmed_str[i]) != NULL)
			arr_len++;
		i++;
	}
	free(trimmed_str);
	return (arr_len);
}

static size_t	get_size(char *str, char *set)
{
	size_t	size;

	size = 0;
	while (*str && ft_strchr(set, *str) == NULL)
	{
		size++;
		str++;
	}
	return (size);
}

char	**ft_split_set(char *str, char *set)
{
	char	**arr;
	int		arr_len;
	int		i;
	int		j;
	bool	inside_quotes;

	i = 0;
	inside_quotes = false;
	if (str == NULL || set == NULL)
		return (NULL);
	int len = 0;
	while (str[len])
		len++;
	char	*test = malloc (sizeof(char) * (len + 1));
	if (!test)
		return (NULL);
	int k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && str[i - 1] != ' ')
		{
			test[k] = ' ';
			k++;
			test[k] = '|';
			k++;
			i++;
		}
		test[k] = str[i];
		k++;
		i++;
	}
	test[k] = '\0';
	str = test;
	// printf ("%s\n", str);
	// exit (0);
	arr_len = get_arr_len(str, set);
	arr = ft_calloc(arr_len + 1, sizeof(*arr));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < arr_len && *str)
	{
		while (*str && ft_strchr(set, *str) != NULL)
			str++;
		arr[i] = ft_calloc(get_size(str, set) + 1, sizeof(*arr[i]));
		if (arr[i] == NULL)
			return (ft_free_split(arr));
		j = 0;
		while (*str && (ft_strchr(set, *str) == NULL || inside_quotes))
		{
			if (*str == '\'' || *str == '"')
				inside_quotes = !inside_quotes;
			arr[i][j++] = *str++;
		}
		i++;
	}
	return (arr);
}

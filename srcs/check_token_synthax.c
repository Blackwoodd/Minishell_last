/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_synthax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:50:37 by nassm             #+#    #+#             */
/*   Updated: 2023/07/25 13:20:13 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

bool	is_redirection(char *token)
{
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, "<<") || ft_strstr(token, ">>"))
			return (true);
	}
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '<') || ft_strchr(token, '>'))
			return (true);
	}
	return (false);
}

bool	is_correct_spe(char	*token)
{
	if (token[0] == '(' && ft_strchr(token, ')'))
		return (true);
	if (ft_strlen(token) != 2)
	{
		if (ft_strstr(token, "&&") || ft_strstr(token, "||")
			|| ft_strstr(token, "<<") || ft_strstr(token, ">>"))
			return (false);
		if (ft_strchr(token, '&'))
			return (false);
	}
	if (ft_strlen(token) != 1)
	{
		if ((ft_strchr(token, '<') && !ft_strstr(token, "<<"))
			|| (ft_strchr(token, '>') && !ft_strstr(token, ">>"))
			|| (ft_strchr(token, '|') && !ft_strstr(token, "||")))
			return (false);
	}
	return (true);
}

bool	is_correct_pipe(char *current, char *next)
{
	if (ft_strlen(current) == 1 && ft_strchr(current, '|'))
	{
		if (next == NULL)
			return (false);
		if (ft_strlen(next) == 2)
		{
			if (ft_strstr(next, "&&") || ft_strstr(next, "||"))
				return (false);
		}
	}
	return (true);
}

bool	is_special(char *token, int type)
{
	if (ft_strlen(token) == 1 && type == 0)
	{
		if ((ft_strchr(token, '<') && !ft_strstr(token, "<<"))
			|| (ft_strchr(token, '>') && !ft_strstr(token, ">>"))
			|| (ft_strchr(token, '|') && !ft_strstr(token, "||")))
			return (true);
	}
	if (ft_strlen(token) == 2 && type == 0)
	{
		if (ft_strstr(token, "<<") || ft_strstr(token, ">>"))
			return (true);
	}
	if (ft_strlen(token) == 2 && type == 3)
	{
		if (ft_strstr(token, "&&") || ft_strstr(token, "||"))
			return (true);
	}
	return (false);
}

bool	valid_syntax_token(char	*token[])
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!verif_is_token(token[i]))
		{
			if (i == 0 || get_lexic_token()[i + 1] == NULL)
				if ((ft_strlen(token[i]) == 2 && ft_strstr(token[i], "&&"))
					|| ft_strstr(token[i], "||"))
					return (false);
			if (get_lexic_token()[i + 1] == NULL)
				if (is_redirection(token[i]))
					return (false);
			if (!is_correct_spe(token[i]))
				return (false);
			if (!is_correct_pipe(token[i], token[i + 1]))
				return (false);
			if (ft_strchr(token[i], '(') && ft_strchr(token[i], ')'))
				if (i != 0 && is_special(token[i - 1], 0))
					return (false);
		}
		i++;
	}
	return (true);
}

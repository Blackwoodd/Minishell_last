/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lex_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:37:02 by nassm             #+#    #+#             */
/*   Updated: 2023/07/26 14:54:33 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_lex_token(char **lex_toks, bool reset)
{
	static char	**static_lex_toks = NULL;

	if (lex_toks == NULL && !reset)
		return (static_lex_toks);
	if (reset)
	{
		static_lex_toks = NULL;
		return (NULL);
	}
	static_lex_toks = lex_toks;
	return (static_lex_toks);
}

void	reset_lex_token(void)
{
	get_lex_token(NULL, true);
}

void	set_lex_token(char **lex_toks)
{
	get_lex_token(lex_toks, false);
}

char	**get_lexic_token(void)
{
	return (get_lex_token(NULL, false));
}
char	*get_current_lex_token(void)
{
	t_iter	*iter;

	iter = get_iter();
	if (iter == NULL)
		return (NULL);
	return (get_lexic_token()[iter[lex]]);
}

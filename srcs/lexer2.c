/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:12:57 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/14 17:13:24 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

int	lexer(char *rline)
{
	char	**token;
	int		exit_status;

	if (!valid_synthax_str(rline))
		return (exit_syntax_error());
	token = ft_split_set(rline, " \t\r\v\f\n");
	if (join_quote(&token) == EXIT_FAILURE)
	{
		ft_free_str_array(&token);
		return (EXIT_FAILURE);
	}
	token = resize_token(token);
	if (token == NULL)
		return (EXIT_FAILURE);
	set_lex_token(token);
	if (!valid_syntax_token(token))
		return (exit_syntax_error());
	exit_status = parser(token);
	ft_free_tab(token);
	reset_lex_token();
	return (exit_status);
}

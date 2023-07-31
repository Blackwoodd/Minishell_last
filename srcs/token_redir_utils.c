/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:58:20 by nassm             #+#    #+#             */
/*   Updated: 2023/07/25 13:21:13 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_token_redir_type(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '>'))
			return (IS_OUT);
		if (ft_strchr(token, '<'))
			return (IS_IN);
		if (ft_strchr(token, '|'))
			return (IS_PIPE);
	}
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, ">>"))
			return (IS_OUT_APPEND);
		if (ft_strstr(token, "<<"))
			return (IS_IN_HEREDOC);
	}
	return (0);
}

bool	try_get_token_redir_buff(char ****buff, size_t **buff_size,
		t_iter **buff_iter)
{
	if ((ft_strchr(get_current_lex_token(), '>')
			&&ft_strlen(get_current_lex_token()) == 1)
		|| (ft_strstr(get_current_lex_token(), ">>")
			&& ft_strlen(get_current_lex_token()) == 2))
	{
		*buff = &get_current_par_token()->out;
		*buff_size = &get_current_par_token()->out_size;
		*buff_iter = &get_iter()[out];
		return (true);
	}	
	else if ((ft_strchr(get_current_lex_token(), '<')
			&& ft_strlen(get_current_lex_token()) == 1)
		|| (ft_strstr(get_current_lex_token(), "<<")
			&& ft_strlen(get_current_lex_token()) == 2))
	{
		*buff = &get_current_par_token()->in;
		*buff_size = &get_current_par_token()->in_size;
		*buff_iter = &get_iter()[in];
		return (true);
	}
	return (false);
}

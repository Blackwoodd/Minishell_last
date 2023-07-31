/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pars_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:36:02 by nassm             #+#    #+#             */
/*   Updated: 2023/07/27 13:32:12 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_tok_type_pipe(t_par_tok *pars_token, t_iter *iter)
{
	pars_token->redir_type = IS_PIPE;
	iter[lex]++;
	iter[par]++;
	if (init_current_pars_token() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	get_current_par_token()->redir_type = IS_PIPE;
	return (EXIT_BREAK);
}

int	get_subshell_token(t_iter *iter)
{
	char		*lex_token;
	t_par_tok	*par_tok;

	if (init_current_pars_token() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	lex_token = get_current_lex_token();
	par_tok = get_current_par_token();
	par_tok->cmd_size++;
	par_tok->cmd = ft_str_arr_realloc(par_tok->cmd, par_tok->cmd_size);
	if (par_tok->cmd == NULL)
		return (EXIT_FAILURE);
	par_tok->cmd[iter[cmd]] = ft_strdup(lex_token);
	if (par_tok->cmd[iter[cmd]] == NULL)
		return (EXIT_FAILURE);
	iter[cmd]++;
	par_tok->type = subshell;
	iter[lex]++;
	return (EXIT_BREAK);
}

bool	is_token_quote(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (true);
	return (false);
}

bool	is_token_redir(char *token)
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
		if (ft_strchr(token, '|'))
			return (true);
	}
	return (false);
}

bool	is_spe_token(char *token)
{
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, "&&") || ft_strstr(token, "||"))
			return (true);
	}
	return (false);
}

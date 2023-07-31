/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:41:35 by nassm             #+#    #+#             */
/*   Updated: 2023/07/27 15:17:44 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_token_cmd(char *token, t_par_tok *par_tok, t_iter *iter)
{
	if (token == NULL)
		return (EXIT_SUCCESS);
	if (!is_token_quote(token) && (is_spe_token(token)
			|| is_token_redir(token) || (ft_strchr(token, '(')
				|| ft_strchr(token, ')'))))
		return (EXIT_SUCCESS);
	if (init_current_pars_token() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	par_tok->cmd_size++;
	par_tok->cmd = ft_str_arr_realloc(par_tok->cmd, par_tok->cmd_size);
	if (par_tok->cmd == NULL)
		return (EXIT_FAILURE);
	par_tok->cmd[iter[cmd]] = ft_strdup(token);
	if (par_tok->cmd[iter[cmd]] == NULL)
		return (EXIT_FAILURE);
	iter[lex]++;
	iter[cmd]++;
	return (EXIT_SUCCESS);
}

int	get_token_redir(char *lex_token[], t_iter *iter)
{
	int		i;
	t_iter	*buff_iter;
	char	***buff;
	size_t	*buff_size;

	if (lex_token[iter[lex]] == NULL)
		return (EXIT_SUCCESS);
	if (!try_get_token_redir_buff(&buff, &buff_size, &buff_iter))
		return (EXIT_SUCCESS);
	// if (init_current_pars_token() == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	get_current_par_token()->redir_type = get_token_redir_type(lex_token[iter[lex]]);
	(*buff_size) += 2;
	*buff = ft_str_arr_realloc(*buff, *buff_size);
	if (*buff == NULL)
		return (EXIT_FAILURE);
	i = 2;
	while (i--)
	{
		(*buff)[*buff_iter] = ft_strdup(lex_token[iter[lex]++]);
		if ((*buff)[(*buff_iter)++] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_special_token(char *token, t_par_tok *par_toks[], t_iter *iter)
{
	if (token == NULL)
		return (EXIT_SUCCESS);
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (EXIT_SUCCESS);
	if ((ft_strstr(token, "&&") || ft_strstr(token, "||"))
		&& ft_strlen(token) == 2)
	{
		iter[par]++;
		if (init_current_pars_token() == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_strstr(token, "&&"))
			par_toks[iter[par]++]->type = and;
		else if (ft_strstr(token, "||"))
			par_toks[iter[par]++]->type = or;
		iter[lex]++;
		return (EXIT_BREAK);
	}
	if (ft_strchr(token, '('))
		return (get_subshell_token(iter));
	return (EXIT_SUCCESS);
}

int	get_token_type(char *token, t_iter *iter)
{
	t_par_tok	*par_tok;

	if (token == NULL)
		return (EXIT_SUCCESS);
	if (init_current_pars_token() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	par_tok = get_current_par_token();
	// if (ft_strlen(token) == 1 && ft_strchr(token, '|'))
	// 	return (set_tok_type_pipe(par_tok, iter));
	par_tok->redir_type = NONE;
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '|'))
			return (set_tok_type_pipe(par_tok, iter));
		if (ft_strchr(token, '<'))
			par_tok->in_redir = IS_IN;
		if (ft_strchr(token, '>'))
			par_tok->out_redir = IS_OUT;
	}
	if (ft_strlen(token) == 2 && ft_strstr(token, "<<"))
		par_tok->in_redir = IS_IN_HEREDOC;
	if (ft_strlen(token) == 2 && ft_strstr(token, ">>"))
		par_tok->out_redir = IS_OUT_APPEND;
	if ((token[0] != '\'' && token[0] != '\"')
		&& (ft_strchr(token, '(') && ft_strchr(token, ')')))
		par_tok->type = subshell;
	return (EXIT_SUCCESS);
}
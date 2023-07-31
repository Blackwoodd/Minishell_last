/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:39:21 by nassm             #+#    #+#             */
/*   Updated: 2023/07/27 16:06:31 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_pars_tok(char *lex_tok[], t_par_tok *pars_tok[], t_iter *iter)
{
	int			tmp;

	tmp = EXIT_SUCCESS;
	tmp = get_token_type(lex_tok[iter[lex]], iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_token_redir(lex_tok, iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_token_cmd(lex_tok[iter[lex]], pars_tok[iter[par]], iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_special_token(lex_tok[iter[lex]], pars_tok, iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	return (EXIT_SUCCESS);
}

int	get_token(char *lexer_token[])
{
	t_par_tok	**pars_token;
	t_iter		*iter;
	int			get_pars_tok_exit_status;

	iter = ft_calloc(NB_ITER + 1, sizeof(*iter));
	if (iter == NULL)
		return (EXIT_FAILURE);
	set_iter(iter);
	pars_token = ft_calloc(get_stoken_size(lexer_token) + 1,
			sizeof(*pars_token));
	if (pars_token == NULL)
	{
		free(iter);
		return (EXIT_FAILURE);
	}
	set_pars_token(pars_token);
	get_pars_tok_exit_status = EXIT_SUCCESS;
	while (lexer_token[iter[lex]])
	{
		get_pars_tok_exit_status = get_pars_tok(lexer_token, pars_token, iter);
		if (get_pars_tok_exit_status == EXIT_FAILURE)
		{
			free_parser(pars_token, iter, EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		else if (get_pars_tok_exit_status == EXIT_SYNTAX_ERROR)
		{
			free_parser(pars_token, iter, EXIT_SYNTAX_ERROR);
			return (EXIT_SYNTAX_ERROR);
		}
	}
	free(iter);
	return (EXIT_SUCCESS);
}

char	**expand_env_var(char *lex_token[])
{
	int	i;

	i = 0;
	while (lex_token[i])
	{
		lex_token[i] = interpret_env_var(lex_token[i]);
		if (lex_token[i] == NULL)
			return (NULL);
		if (ft_strstr(lex_token[i], "&&") || ft_strstr(lex_token[i], "|"))
			break ;
		i++;
	}
	return (lex_token);
}

int	parser(char *lexer_token[])
{
	t_par_tok	**token;
	int			exit_code;

	lexer_token = expand_env_var(lexer_token);
	if (lexer_token == NULL)
		return (EXIT_FAILURE);
	set_lex_token(lexer_token);
	exit_code = get_token(lexer_token);
	if (exit_code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (exit_code == EXIT_SYNTAX_ERROR)
		return (EXIT_SYNTAX_ERROR);
	token = get_pars_token();
	ft_free_tab(lexer_token);
	return (free_pars_token(token, expander(token)));
}
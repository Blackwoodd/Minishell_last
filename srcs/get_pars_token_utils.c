/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pars_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:36:02 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 17:06:41 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is responsible to set Sets current and next token type to pipe
*/

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

/*
	The function s responsible for handling subshell tokens during parsing.

	* The function takes a parameter iter, which is a pointer to the iterator array.
    
	* It first calls the function init_current_pars_token to initialize the
	current parser token.
	If the initialization fails (EXIT_FAILURE), the function returns EXIT_FAILURE.
    
	* It then retrieves the current lexical token array using get_current_lex_token
	and assigns it to the lex_token variable.
    
	* The function obtains the current parser token using get_current_par_token
	and assigns it to the par_token variable.
    
	* The function increments the cmd_size field of the parser token
	to account for the subshell token.
    
	* It reallocates memory for the cmd array in the parser token using
	ft_str_arr_realloc to accommodate the increased size.
	If the reallocation fails, the function returns EXIT_FAILURE.
    
	* The function assigns the current lexical token (lex_token)
	to the cmd array at the index specified by iter[cmd] using ft_strdup.
	If the duplication fails, the function returns EXIT_FAILURE.
    
	* The iter[cmd] index is incremented to move to the next command element
	in the parser token.
    
	* The type field of the parser token is set to subshell to
	indicate that it represents a subshell.
    
	* The iter[lex] index is incremented to move to the next lexical token.
    
	* Finally, the function returns EXIT_BREAK to indicate a
	successful parsing of the subshell token.
*/

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

/*
	The function checks whether a given token contains single or double quotes.
*/

bool	is_token_quote(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (true);
	return (false);
}

/*
	The function checks whether a given token represents a redirection operator.
*/

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

/*
	The function checks whether a given token represents a special operator. 
*/

bool	is_spe_token(char *token)
{
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, "&&") || ft_strstr(token, "||"))
			return (true);
	}
	return (false);
}

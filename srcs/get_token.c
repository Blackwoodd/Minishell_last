/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:41:35 by nassm             #+#    #+#             */
/*   Updated: 2023/05/30 16:36:35 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is used to handle a token that represents a command within
	the parsing process.

	*The function first checks if the token is NULL. If so, it returns
	EXIT_SUCCESS to indicate that the token handling is complete.
    
	*Next, it checks if the token is not a quote token (is_token_quote(token))
	and is either a special token (is_spe_token(token)),
	a redirection token (is_token_redir(token)), or contains parentheses
	(ft_strchr(token, '(') or ft_strchr(token, ')')).
	If this condition is true, it returns EXIT_SUCCESS to
	indicate that the token handling is complete.
    
	*If the token passes the above conditions, it proceeds to initialize
	the current parsing token (init_current_pars_token()).
	If the initialization fails (EXIT_FAILURE), it returns EXIT_FAILURE
	to indicate an error.
    
	*The function then increments the command size (par_tok->cmd_size++)
	and reallocates the command array with the updated size
	(par_tok->cmd = ft_str_arr_realloc(par_tok->cmd, par_tok->cmd_size)).
	If the reallocation fails (NULL), it returns EXIT_FAILURE
	to indicate an error.
    
	*It assigns the token to the current command array at the command iterator
	index (par_tok->cmd[iter[cmd]] = ft_strdup(token)). If the duplication
	fails (NULL), it returns EXIT_FAILURE to indicate an error.
    
	*It increments the lex and command iterators (iter[lex]++ and iter[cmd]++).
    
	*Finally, it returns EXIT_SUCCESS to indicate successful token handling.
*/

int	get_token_cmd(char  *token, t_par_tok *par_tok, t_iter *iter)
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

/*
	The function is responsible for handling a token that
	represents a redirection within the parsing process.

	*The function first checks if the current lex_token is NULL.
	If so, it returns EXIT_SUCCESS to indicate that the token handling is complete.

	*Next, it attempts to retrieve the appropriate buffer and buffer iterators
	for the redirection using the try_get_token_redir_buff function.
	If this attempt fails, it returns EXIT_SUCCESS to indicate that
	the token handling is complete.

	*If the redirection buffer and iterators are successfully obtained,
	the function proceeds to initialize the current parsing
	token using init_current_pars_token().
	If the initialization fails (EXIT_FAILURE),
	it returns EXIT_FAILURE to indicate an error.

	*The function sets the corresponding redirection type
	in the current parsing token based on the
	token's type (get_current_par_tok()->redir_type[get_token_redit_type(lex_token[iter[lex]])] = true).

	*The function increments the buffer size by 2 ((*buff_size) += 2)
	to account for the redirection tokens.

	*The buffer is then reallocated with the updated
	size (*buff = ft_str_arr_realloc(*buff, *buff_size)).
	If the reallocation fails (NULL),
	it returns EXIT_FAILURE to indicate an error.

	*Using a loop with two iterations, the function performs the following steps:

    	-Duplicates the lex_token at the current lex iterator index and
		assigns it to the buffer at the current buffer
		iterator index ((*buff)[*buff_iter] = ft_strdup(lex_token[iter[lex]++])).
    
		-If the duplication fails (NULL), it returns EXIT_FAILURE to indicate an error.
    
		-Increments the buffer iterator ((*buff_iter)++).

	* Finally, it returns EXIT_SUCCESS to indicate successful token handling.
*/

int get_token_redir(char *lex_token[], t_iter *iter)
{
	int		i;
	t_iter	*buff_iter;
	char	***buff;
	size_t	*buff_size;
	
	if (lex_token[iter[lex]] == NULL)
		return (EXIT_SUCCESS);
	if (!try_get_token_redir_buff(&buff, &buff_size, &buff_iter))
		return(EXIT_SUCCESS);
	if (init_current_pars_token() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	get_current_par_token()->redir_type \
	[get_token_redir_type(lex_token[iter[lex]])] = true;
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

/*
	The function handles special tokens during the parsing process.

	*The function first checks if the token is NULL. If so,
	it returns EXIT_SUCCESS to indicate that the token handling is complete.
	
	*Next, it checks if the token contains single quotes or double quotes.
	If so, it returns EXIT_SUCCESS to indicate that the token is
	a quote and should be skipped.

	*If the token is a special token (i.e., "&&" or "||") and has a
	length of 2, the function proceeds to handle it as follows:

    *Increments the paragraph iterator (iter[par]++) to
	move to the next paragraph.
    
	*Initializes the current paragraph token using init_current_pars_token().
	If the initialization fails (EXIT_FAILURE), it returns EXIT_FAILURE to indicate an error.

	*Sets the type of the current paragraph token based on the special token:
    
	*If the token is "&&", the type is set to "and".
    
	*If the token is "||", the type is set to "or".
    
	*Increments the lex iterator (iter[lex]++) to move to the next lex token.
    
	*Returns EXIT_BREAK to indicate that the current paragraph token handling is complete.

	*If the token contains an opening parenthesis ((), it calls the get_subshell_token
	function to handle the subshell token using the current iterator (iter) and returns its result.

	*If none of the above conditions are met, it returns EXIT_SUCCESS to
	indicate that the token handling is complete.
*/

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
		return(get_subshell_token(iter));
	return (EXIT_SUCCESS);
}

/*
	The function is responsible for determining the type of a
	token during the parsing process.

	*The function first checks if the token is NULL. If so, it returns EXIT_SUCCESS
	to indicate that the token handling is complete.
    
	*Next, it initializes the current paragraph token using init_current_pars_token().
	If the initialization fails (EXIT_FAILURE), it returns EXIT_FAILURE to indicate an error.
    
	*The function retrieves a pointer to the current paragraph token (par_tok)
	for easier access to its attributes.
    
	*If the token has a length of 1, the function checks the following conditions:
        
		-If the token contains a pipe symbol (|), it calls the set_tok_type_pipe
		function to set the token type as a pipe and updates the iterators accordingly.
        
		-If the token contains a less-than symbol (<),
		it sets the is_in flag of the paragraph token's redir_type attribute to true.
        
		-If the token contains a greater-than symbol (>),
		it sets the is_out flag of the paragraph token's redir_type attribute to true.
    
	*If the token has a length of 2 and contains the substring "<<",
	it sets the is_in_heredoc flag of the paragraph token's redir_type attribute to true.
    
	*If the token has a length of 2 and contains the substring ">>",
	it sets the is_out_append flag of the paragraph token's redir_type attribute to true.
    
	*Finally, if the token does not start with a single quote or 
	double quote and contains both an opening parenthesis and a closing parenthesis,
	it sets the type of the paragraph token to "subshell".
    
	*The function returns EXIT_SUCCESS to indicate that the token type handling is complete.
*/

int	get_token_type(char *token, t_iter *iter)
{
	t_par_tok	*par_tok;

	if (token == NULL)
		return (EXIT_SUCCESS);
	if (init_current_pars_token() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	par_tok = get_current_par_token();
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '|'))
			return (set_tok_type_pipe(par_tok, iter));
		if (ft_strchr(token, '<'))
			par_tok->redir_type[is_in] = true;
		if (ft_strchr(token, '>'))
			par_tok->redir_type[is_out] = true;
	}
	if (ft_strlen(token) == 2 && ft_strstr(token, "<<"))
		par_tok->redir_type[is_in_heredoc] = true;
	if (ft_strlen(token) == 2 && ft_strstr(token, ">>"))
		par_tok->redir_type[is_out_append] = true;
	if ((token[0] != '\'' && token[0] != '\"')
			&& (ft_strchr(token, '(') && ft_strchr(token, ')')))
		par_tok->type = subshell;
	return (EXIT_SUCCESS);
}

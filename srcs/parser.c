/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:39:21 by nassm             #+#    #+#             */
/*   Updated: 2023/07/04 16:08:31 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is a static function that processes the lexical
	tokens and updates the corresponding paragraph tokens.
	
	* The function takes an array of lexical tokens lex_tok[], an array of
	paragraph tokens pars_tok[], and an iterator iter as input.
    
	* It initializes a temporary variable tmp with the value EXIT_SUCCESS.
    
	*The function calls get_token_type to determine the type of the
	current lexical token at lex_tok[iter[lex]].
	It passes the iter iterator to keep track of the current position.
	The result of get_token_type is stored in tmp.
	If tmp is not equal to EXIT_SUCCESS, indicating an error,
	the function returns tmp.
    
	* The function then calls get_token_redir to handle redirection tokens
	in lex_tok. It passes lex_tok and iter as arguments.
	If the result is not EXIT_SUCCESS, indicating an error,
	the function returns tmp.
    
	* Next, the function calls get_token_cmd to handle command tokens.
	It passes the current lexical token at lex_tok[iter[lex]],
	the current paragraph token at pars_tok[iter[par]], and iter as arguments.
	If the result is not EXIT_SUCCESS, the function returns tmp.
    
	* Finally, the function calls get_special_token to handle special tokens
	such as logical operators and subshell tokens. It passes the current
	lexical token, the array of paragraph tokens pars_tok, and iter as arguments.
	If the result is not EXIT_SUCCESS, the function returns tmp.
    
	* If all the token handling steps are completed successfully,
	the function returns EXIT_SUCCESS to indicate successful
	processing of the paragraph tokens.
*/

int	get_pars_tok(char *lex_tok[], t_par_tok *pars_tok[], t_iter *iter)
{
	int	tmp;
	
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

/*
	The function is a static function that processes the lexer tokens
	and populates the paragraph tokens.

	*The function takes an array of lexer tokens lexer_token[] as input.
    
	*It declares variables pars_token of type t_par_tok (paragraph tokens)
	and iter of type t_iter (iterator).
    
	*The function allocates memory for the iter variable using ft_calloc
	to store the iterator values. If the memory allocation fails,
	the function returns EXIT_FAILURE.
    
	*The function sets the iterator values using the set_iter function,
	passing the iter variable.
    
	*The function allocates memory for the pars_token array using
	ft_calloc based on the size of the lexer tokens.
	If the memory allocation fails, the function returns EXIT_FAILURE.
    
	*The function sets the paragraph tokens using the set_pars_token function,
	passing the pars_token array.
    
	*The function enters a loop that iterates through each lexer
	token in lexer_token[iter[lex]].
    
	*Within the loop, it calls the get_pars_tok function to process
	the current lexer token, the pars_token array, and the iter iterator.
	The result of get_pars_tok is stored in the get_pars_tok_estatus variable.
    
	*If get_pars_tok_estatus is EXIT_FAILURE, indicating an error,
	the function frees the memory allocated for pars_token and iter using
	the free_parser function and returns EXIT_FAILURE.
    
	*If get_pars_tok_estatus is EXIT_SYNTAX_ERROR, indicating a syntax error,
	the function frees the memory allocated for pars_token and iter
	using the free_parser function and returns EXIT_SYNTAX_ERROR.
    
	*After processing all the lexer tokens, the function frees the
	memory allocated for iter.
    
	*Finally, the function returns EXIT_SUCCESS to indicate
	successful processing of the tokens.
*/

/*
static int	get_token(char *lexer_token[])
{
		t_par_tok	**pars_token;
		t_iter		*iter;
		int			get_pars_tok_estatus;

		iter = ft_calloc(NB_ITER + 1, sizeof(*iter));
		if (iter == NULL)
			return (EXIT_FAILURE);
		set_iter(iter);
		pars_token = ft_calloc(get_stoken_size(lexer_token) + 1, sizeof(*pars_token));
		if (pars_token == NULL)
			return (EXIT_FAILURE);
		set_pars_token(pars_token);
		while (lexer_token[iter[lex]])
		{
			get_pars_tok_estatus = get_pars_tok(lexer_token, pars_token, iter);
			if (get_pars_tok_estatus == EXIT_FAILURE)
				return (free_parser(pars_token, iter, EXIT_FAILURE));
			else if (get_pars_tok_estatus == EXIT_SYNTAX_ERROR)
				return (free_parser(pars_token, iter, EXIT_SYNTAX_ERROR));
		}
		free(iter);
		return (EXIT_SUCCESS);
}
*/

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

/*
	The function takes an array of lexer tokens lex_token[]
	as input and expands any environment variables present in the tokens.

	*The function declares an integer variable i and initializes it to 0.
    
	*It enters a loop that iterates through each lexer token in lex_token[i].
    
	*Within the loop, it calls the interpret_env_var function to interpret and
	expand the environment variable in the current lexer token.
	The result is stored back in lex_token[i].
    
	*If the result of interpret_env_var is NULL, indicating an
	error occurred during variable expansion, the function returns NULL.
    
	*The function then checks if the expanded lexer token contains the
	substrings "&&" or "|". If either of these substrings is found,
	it breaks out of the loop.
    
	*If neither "&&" nor "|" is found in the expanded lexer token,
	it increments i and continues to the next lexer token.
    
	*After processing all the lexer tokens, the function returns
	the modified lex_token array.
*/

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

/*
	*The function calls the interpret_env_var function to expand environment
	variables in the lexer_token array. The result is stored
	back in lexer_token.

	*If the result of interpret_env_var is NULL, indicating an error
	occurred during variable expansion, the function returns EXIT_FAILURE.

	*The function then sets the lexer_token array using the
	set_lex_token function.

	*It calls the get_token function to perform tokenization and parsing
	on the lexer_token array.
	
	*The return value of get_token is stored in the exit_code variable.

	*If the exit_code is EXIT_FAILURE, indicating an error occurred during 
	okenization or parsing, the function returns EXIT_FAILURE.

	*If the exit_code is EXIT_SYNTAX_ERROR, indicating a syntax error was
	encountered during parsing, the function returns EXIT_SYNTAX_ERROR.

	*The function retrieves the current parsed tokens using the
	get_current_par_token function and assigns them to the token variable.
*/

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

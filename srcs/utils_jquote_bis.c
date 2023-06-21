/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_jquote_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:13:34 by nassm             #+#    #+#             */
/*   Updated: 2023/06/21 16:56:37 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is responsible for combining multiple tokens within a 
	specified quote type (single or double quotes).

	* The function enters a loop that continues as long as 
	there are tokens (*token) and the current token ((*token)[quote->i]) 
	does not contain the quote character (quote->quote).

	* Within each iteration of the loop, the function uses ft_strstrjoin 
	to concatenate the current token ((*token)[quote->i]) with itself,
	separated by a space, effectively combining the token.

	* If the concatenation operation fails (resulting in a NULL value),
	the function returns EXIT_FAILURE to indicate a failure.

	* The original token at index quote->i is freed using 
	ft_free_single_str to release memory.

	* The loop continues to the next iteration,
	combining the subsequent tokens until a token containing 
	the quote character is encountered.

	*Once the loop ends,
	the function returns EXIT_SUCCESS to indicate
	s a successful combination of tokens.
*/

int	combine_loop(char ***token, t_quote *quote)
{
	while (*token && (*token)[quote->i]
			&& ft_setinstr((*token)[quote->i], quote->quote) == false)
	{
		(*token)[quote->j] = ft_strstrjoin((*token)[quote->i],
				(*token)[quote->i], " ");
		if ((*token)[quote->j] == NULL)
			return (EXIT_FAILURE);
		ft_free_single_str(token, quote->i);
	}
	return (EXIT_SUCCESS);
}

/*
	the token_join_end_one function is responsible for handling the joining 
	and splitting of tokens based on quotes, ensuring the correct 
	manipulation of tokens within the tokens array.
*/

int	token_join_end_one(char ***token, t_quote *quote)
{
	quote->end = ft_strdup((*token)[quote->i]);
	if (quote->end == NULL)
		return (EXIT_FAILURE);
	quote->len = ft_strclen(quote->end, *quote->quote) + 1;
	(*token)[quote->j] = ft_append_len_div(&(*token)[quote->j],
			quote->end, quote->len, " ");
	if ((*token)[quote->j] == NULL)
		return (EXIT_FAILURE);
	if (quote->end[quote->len] == '\0')
		ft_free_single_str(token, quote->i);
	else
	{
		ft_free_str(&(*token)[quote->i]);
		(*token)[quote->i] = ft_strdup(quote->end + quote->len);
		if ((*token)[quote->i] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

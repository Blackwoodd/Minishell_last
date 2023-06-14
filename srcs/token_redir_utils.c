/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:58:20 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 17:17:59 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is used to determine the redirection type of a token.

	* The function takes a parameter token, which is a string
	representing a token.
    
	* It first checks the length of the token using ft_strlen.
    
	* If the length of the token is 1, it checks if the token contains any
	of the characters '>', '<', or '|'. If found, it returns the corresponding
	redirection type: is_out for '>', is_in for '<', and is_pipe for '|'.
    
	* If the length of the token is 2, it checks if the token contains either ">>"
	or "<<". If found, it returns the corresponding redirection type: is_out_append
	for ">>" and is_in_heredoc for "<<".
    
	* If none of the above conditions are met, it returns 0,
	indicating that the token is not a redirection operator.
*/

int	get_token_redir_type(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '>'))
			return (is_out);
		if (ft_strchr(token, '<'))
			return (is_in);
		if (ft_strchr(token, '|'))
			return (is_pipe);
	}
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, ">>"))
			return (is_out_append);
		if (ft_strstr(token, "<<"))
			return (is_in_heredoc);
	}
	return (0);
}

/*
	The function s used to attempt to retrieve the appropriate buffer,
	buffer size, and buffer iterator for a given token that
	represents a redirection operator.

	* The function first checks if the current lex token contains either '>'
	or '>>' and has a length of 1 or 2, respectively.
	If this condition is met, it assumes that the token represents an
	output redirection.
    
		- If the above condition is true, it assigns the address
		of the output buffer (get_curr_par_token()->out),
		the address of the output buffer size (get_curr_par_token()->out_size),
		and the address of the output buffer iterator (&get_iter()->out) to
		the corresponding variables passed as parameters (buff, buff_size,
		buff_iter).
		-It returns true to indicate that the retrieval was successful.
    
	* If the above condition is not true, it checks if the current lex token
	contains either '<'or '<<' and has a length of 1 or 2, respectively.
	If this condition is met, it assumes that the token represents an input
	redirection.
		
		- If the input redirection condition is true, it assigns
		the address of the input buffer (get_curr_par_token()->in),
		the address of the input buffer size (get_curr_par_token()->in_size),
		and the address of the input buffer iterator (&get_iter()->in) to
		the corresponding variables passed as parameters (buff, buff_size, buff_iter).
		- It returns true to indicate that the retrieval was successful.
    
	* If none of the above conditions are met, it returns false to
	indicate that the token does not represent a valid redirection operator.
*/

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

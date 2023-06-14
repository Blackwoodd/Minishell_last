/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:42:27 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 17:19:44 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function determines the type of pipe to be used based on the tokens
	in the given array par_toks. It takes as input the array of
	t_par_tok structures and the index i indicating
	the current position in the array.

	*If the current token does not have a pipe redirection (is_pipe is false),
	it returns -1 indicating no pipe type.
    
	*If the current token has a pipe redirection and the previous token also
	has a pipe redirection, and the next token is either NULL or
	does not have a pipe redirection, it sets pipe_type to 0.
    
	*If the previous token does not have a pipe redirection,
	the current token has a pipe redirection, the next token is not NULL,
	and the next token has a pipe redirection, it sets pipe_type to 1.
    
	*If the previous token has a pipe redirection, the current token has
	a pipe redirection, the next token is not NULL, and the next token has
	a pipe redirection, it sets pipe_type to 2.
    
	*If the current token has a pipe redirection, and the next token
	is not NULL and has a pipe redirection, it sets pipe_type to 1.
    
	*If none of the above conditions are met,
	it returns -1 indicating no pipe type.
*/

int	set_pipe_type(t_par_tok **par_toks, int i)
{
	int	pipe_type;

	pipe_type = -1;
	if (par_toks[i]->redir_type[is_pipe] == false)
		return (pipe_type);
	else if (i > 0)
	{
		if (par_toks[i - 1]->redir_type[is_pipe]
			&& par_toks[i]->redir_type[is_pipe] && (par_toks[i + 1] == NULL
				|| par_toks[i + 1]->redir_type[is_pipe] == false))
			pipe_type = 0;
		else if (par_toks[i - 1]->redir_type[is_pipe] == false
			&& par_toks[i]->redir_type[is_pipe] && par_toks[i + 1] != NULL
			&& par_toks[i + 1]->redir_type[is_pipe])
			pipe_type = 1;
		else if (par_toks[i - 1]->redir_type[is_pipe]
			&& par_toks[i]->redir_type[is_pipe] && par_toks[i + 1] != NULL
			&& par_toks[i + 1]->redir_type[is_pipe])
			pipe_type = 2;
	}
	else if (par_toks[i]->redir_type[is_pipe] && par_toks[i + 1] != NULL
		&& par_toks[i + 1]->redir_type[is_pipe])
		pipe_type = 1;
	return (pipe_type);
}

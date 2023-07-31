/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:42:27 by nassm             #+#    #+#             */
/*   Updated: 2023/07/25 14:06:10 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe_type	set_pipe_type(t_par_tok **par_toks, int i)
{
	if (par_toks[i]->redir_type != IS_PIPE)
		return (NOT_PIPE);
	else if (i > 0)
	{
		if (par_toks[i - 1]->redir_type == IS_PIPE &&
			par_toks[i]->redir_type == IS_PIPE &&
			(par_toks[i + 1] == NULL || par_toks[i + 1]->redir_type != IS_PIPE))
			return END_PIPE;
		else if (
			par_toks[i - 1]->redir_type != IS_PIPE &&
			par_toks[i]->redir_type == IS_PIPE &&
			par_toks[i + 1] != NULL &&
			par_toks[i + 1]->redir_type == IS_PIPE)
			return START_PIPE;
		else if (
			par_toks[i - 1]->redir_type == IS_PIPE &&
			par_toks[i]->redir_type == IS_PIPE &&
			par_toks[i + 1] != NULL
			&& par_toks[i + 1]->redir_type == IS_PIPE
			)
			return MIDDLE_PIPE;
	} else if (
		par_toks[i]->redir_type == IS_PIPE &&
		par_toks[i + 1] != NULL &&
		par_toks[i + 1]->redir_type == IS_PIPE
		)
		return START_PIPE;
	return (NOT_PIPE);
}

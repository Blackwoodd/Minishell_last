/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pars_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:08:44 by nassm             #+#    #+#             */
/*   Updated: 2023/07/26 14:55:08 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_par_tok	**get_pars_toke(t_par_tok **pars_token, bool reset)
{
	static t_par_tok	**static_pars_token = NULL;

	if (pars_token == NULL && !reset)
		return (static_pars_token);
	if (reset)
	{
		static_pars_token = NULL;
		return (NULL);
	}
	static_pars_token = pars_token;
	return (static_pars_token);
}

t_par_tok	**get_pars_token(void)
{
	return (get_pars_toke(NULL, false));
}

t_par_tok	*get_current_par_token(void)
{
	t_iter	*iter;

	iter = get_iter();
	if (iter == NULL)
		return (NULL);
	return (get_pars_token()[iter[par]]);
}

void	set_pars_token(t_par_tok **pars_token)
{
	get_pars_toke(pars_token, false);
}

void	reset_pars_token(void)
{
	get_pars_toke(NULL, true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pars_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:08:44 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 16:34:07 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The functionis responsible for retrieving and managing a static variable
	static_pars_token, which stores a pointer to
	an array of t_par_tok structures.
*/

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

/*
	The function retrieves the current t_par_tok token from the t_par_tok array.

	* It first calls the get_iter function to retrieve the current iterator iter.

	* If iter is NULL, indicating that there is no valid iterator,
	it returns NULL indicating no current token.
	
	* Otherwise, it calls the get_pars_token function to retrieve
	the t_par_tok array and accesses the element at the index iter[par].

	* It returns the retrieved t_par_tok token.
*/

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

/*
	The function is a void function that resets the t_par_tok array
	to its initial state. 
*/

void	reset_pars_token(void)
{
	get_pars_toke(NULL, true);
}

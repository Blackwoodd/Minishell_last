/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:29:51 by nassm             #+#    #+#             */
/*   Updated: 2023/05/30 15:53:28 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	This functionis used to get and set the value of static_iter.
	
	*When iter is NULL and reset is false, the function returns
	the value of static_iter.
    
	*When reset is true, the function resets the value of
	static_iter to NULL and returns NULL.
    
	*When neither iter is NULL nor reset is true, the function
	sets the value of static_iter to iter and returns static_iter.
*/

#include "../include/minishell.h"

static t_iter	*get_iter_core(t_iter *iter, bool reset)
{
	static t_iter	*static_iter = NULL;
	
	if (iter == NULL && !reset)
		return (static_iter);
	if (reset)
	{
		static_iter = NULL;
		return (NULL);
	}
	static_iter = iter;
	return (static_iter);
}

t_iter	*get_iter(void)
{
	return (get_iter_core(NULL, false));
}

void	set_iter(t_iter *iter)
{
	get_iter_core(iter, false);
}

void	reset_iter(void)
{
	get_iter_core(NULL, true);
}
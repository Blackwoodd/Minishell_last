/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:18:45 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 16:39:32 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function s a static function that manages
	a static variable static_envar, which holds a pointer
	to an instance of the t_env structure.

	* If envar is NULL, indicating a request to retrieve
	the current value of static_envar,
	the function returns the value of static_envar.

	* If envar is not NULL, indicating a request to set a new value for
	static_envar, the function assigns the value of envar to static_envar
	and returns the updated value of static_envar.
*/

static t_env	*get_env_v(t_env	*envar)
{
	static t_env	*static_envar = NULL;

	if (envar == NULL)
		return (static_envar);
	static_envar = envar;
	return (static_envar);
}

/*
	The functioncalls the get_env_v function
	to set the value of the static variable static_envar
	to the provided envar argument. 
*/

void	set_envar(t_env *envar)
{
	get_env_v(envar);
}

t_env	*get_envar(void)
{
	return (get_env_v(NULL));
}

/*
	The functionis used to retrieve the array of environment
	variable values from the envar structure.

*/

char	**get_env_var(void)
{
	t_env	*envar;

	envar = get_envar();
	if (envar == NULL)
		return (NULL);
	return (envar->env_var);
}

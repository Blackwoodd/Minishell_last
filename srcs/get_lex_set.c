/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lex_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:37:02 by nassm             #+#    #+#             */
/*   Updated: 2023/05/30 16:11:48 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The purpose of the _get_lex_toks function 
	is to manipulate a static variable static_lex_toks 
	that stores a pointer to a dynamic array of strings (char **).
	The function allows retrieving the current value of the array, 
	resetting it to NULL, or setting new values to the array.
	It provides a way to manage and access the array across multiple function 
	calls within the same source file.
*/

char	**get_lex_token(char **lex_toks, bool reset)
{
	static char	**static_lex_toks = NULL;

	if (lex_toks == NULL && !reset)
		return (static_lex_toks);
	if (reset)
	{
		static_lex_toks = NULL;
		return (NULL);
	}
	static_lex_toks = lex_toks;
	return (static_lex_toks);
}

/*
	The reset_lex_token function serves 
	as a wrapper function that specifically resets the token array 
	by calling get_lex_token with NULL as the parameter for token
	and true for reset. This simplifies the process of resetting the array 
	in a more readable and concise manner.
*/
void	reset_lex_token(void)
{
	get_lex_token(NULL, true);
}

/*
The purpose of the set_lex_token function
is to set the value of the token array.
It achieves this by calling the get_lextoken function with
token as the parameter and false as the value for the reset parameter.
Essentially, it acts as a wrapper function that simplifies the process of
 setting the token array by invoking the underlying logic 
 of the get_lex_token function.
*/

void	set_lex_token(char **lex_toks)
{
	get_lex_token(lex_toks, false);
}

/*
	The purpose of the get_lexic_token function is to retrieve
	the current value of the lexical tokens array.
	It achieves this by calling the get_lex_token function 
	with NULL as the parameter for token and false for reset.
	The function acts as a simple wrapper that abstracts away the details
	of accessing the lexical tokens array
	and provides a convenient way to obtain its value.
*/

char	**get_lexic_token(void)
{
	return (get_lex_token(NULL, false));
}

/*
	The functionis used to retrieve the current lexical
	token from the token array during shell execution.

	* It does so by accessing the token array using the iterator iter obtained from
	the get_iter() function.
	
	* If the iterator iter is NULL, indicating an error or uninitialized state,
	the function returns NULL.

	* Otherwise, the function calls get_lexic_token() to retrieve the token array
	and uses the iterator iter to access the current lexical token.
	
	* Finally, it returns the pointer to the current lexical token.
*/

char	*get_current_lex_token(void)
{
	t_iter	*iter;

	iter = get_iter();
	if (iter == NULL)
		return (NULL);
	return (get_lexic_token()[iter[lex]]);
}
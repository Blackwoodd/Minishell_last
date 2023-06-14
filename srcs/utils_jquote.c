/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_jquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:27:55 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 17:04:49 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

/*
	The function is responsible for handling the initial token 
	when encountering a quote character (single or double quotes) at the start.

	* The function adds quote->start to the *token array at index quote->i 
	using ft_add_str_to_tab. If the addition fails (resulting in a NULL value),
	the function returns EXIT_FAILURE to indicate an error.

	*The function reallocates memory for (*token)[quote->i] 
	to adjust its size to quote->len, which removes any excess characters
	after the quote character.
	If the reallocation fails (resulting in a NULL value),
	the function returns EXIT_FAILURE.

	* The variable quote->i is incremented to move
	to the next position in the *token array.

	* If the length of quote->start is greater than 1
	and the remaining substring after the first character contains
	the quote character (quote->quote), the function performs additional steps.

	* It assigns the substring after the first character,
	obtained using ft_strdup and ft_strchr, to quote->end.

	* Memory for (*token)[quote->i] is reallocated to adjust 
	its size to the length of quote->start + 1,
	effectively removing any excess characters after the second quote character.

	* If the length of quote->end is greater than or equal to 1,
	it adds quote->end to the *token array at index quote->i using
	ft_add_str_to_tab.

	* The function returns EXIT_SUCCESS after these steps.

	* If the above conditions are not met,
	the function sets quote->j equal to quote->i and increments quote->i
	to prepare for subsequent iterations. It returns 2 to indicate
	that additional processing is required.
*/
int	first_start(char ***token, t_quote *quote)
{
	*token = ft_add_str_to_tab((token), quote->i, quote->start);
	if (*token == NULL)
		return (EXIT_FAILURE);
	(*token)[quote->i] = ft_realloc_str((*token)[quote->i], quote->len);
	if ((*token)[quote->i] == NULL)
		return (EXIT_FAILURE);
	quote->i++;
	if (ft_strlen(quote->start) > 1
		&& ft_setinstr(quote->start +1, quote->quote))
	{
		quote->end = ft_strdup(ft_strchr(quote->start +1, *quote->quote) + 1);
		(*token)[quote->i] = ft_realloc_str((*token)[quote->i],
				ft_strclen(quote->start +1, *quote->quote +2));
		if (ft_strlen(quote->end) >= 1)
			*token = ft_add_str_to_tab(token, quote->i, quote->end);
		return (EXIT_SUCCESS);
	}
	quote->j = quote->i;
	quote->i++;
	return (2);
}

/*
	The function second_start_norm is a helper function
	used within another function.
	It modifies the quote->end and (*token)[quote->j]
	based on certain conditions.

	* If the length of quote->end is greater than or equal to 2,
	the function proceeds with further steps.
	{
	* The function creates a new string by duplicating quote->end starting 
	from the second character (quote->end + 1) using ft_strdup.
	If the duplication fails (resulting in a NULL value),
	the function returns EXIT_FAILURE to indicate an error.

	* The memory allocated for (*token)[quote->j] (the previous token)
	is reallocated using ft_realloc_str to adjust its size
	based on the length of the modified token.
	If the reallocation fails, the function returns EXIT_FAILURE.
	}

	*  If the length of quote->end is less than 2,
	indicating that it is empty or contains only one character,
	quote->end is set to NULL.
	
	* The function returns EXIT_SUCCESS after these steps.
*/
int	second_start_norm(char ***token, t_quote *quote)
{
	if (ft_strlen(quote->end) >= 2)
	{
		quote->end = ft_strdup(quote->end +1);
		if (quote->end == NULL)
			return (EXIT_FAILURE);
		(*token)[quote->j] = ft_realloc_str((*token)[quote->j],
				ft_strclen((*token)[quote->j] + 1, *quote->quote) + 2);
		if ((*token)[quote->j] == NULL)
			return (EXIT_FAILURE);
	}
	else
		quote->end = NULL;
	return (EXIT_SUCCESS);
}

/*
	The functionis responsible for handling the second occurrence 
	of a quotation mark (either single or double) within the token array.

	* The variable quote->i is incremented to move
	to the next token in the array.

	* If the current token ((*token)[quote->i]) contains
	the same quotation mark as quote->quote,
	the function proceeds with further steps:
	{
		- The function concatenates the current token with 
		itself using ft_strstrjoin and a space as the separator.
		The result is stored back in the same token position.
		If the concatenation fails (resulting in a NULL value),
		the function returns EXIT_FAILURE to indicate an error.

		- The function searches for the next occurrence 
		of the quotation mark (*quote->quote) starting from the character
		following the previous occurrence within the token (*token)[quote->j].
		The result is stored in quote->end.
		
		- The function calls the helper function second_start_norm
		to modify quote->end and (*token)[quote->j] based on certain conditions.
		If second_start_norm returns EXIT_FAILURE, indicating an error,
		the function returns EXIT_FAILURE as well.

		- If the length of quote->end is greater than or equal to 1,
		indicating that there are characters following the quotation mark,
		the function proceeds with further steps.
		{
			- The memory allocated for (*token)[quote->i] (the current token) 
			is freed using ft_free_str, and then the token is replaced with
			a duplicated version of quote->end using ft_strdup.
			If the duplication fails (resulting in a NULL value),
			the function returns EXIT_FAILURE.
		}
		If the length of quote->end is less than 1,
		indicating that it is empty, 
		the current token is freed using ft_free_single_str.

		- The function returns EXIT_SUCCESS to indicate successful execution.
	}
	
	* If the current token does not contain the same quotation mark as quote->quote,
	the function returns 2, indicating that further processing is required.
*/

int	second_start(char ***token, t_quote *quote)
{
	quote->i++;
	if (ft_setinstr((*token)[quote->i], quote->quote) == true)
	{
		(*token)[quote->j] = ft_strstrjoin((*token)[quote->j],
				(*token)[quote->i], " ");
		if ((*token)[quote->i] == NULL)
			return (EXIT_FAILURE);
		quote->end = ft_strchr((*token)[quote->j] + 1, *quote->quote);
		if (second_start_norm(token, quote) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_strlen(quote->end) >= 1)
		{
			ft_free_str(&(*token)[quote->i]);
			(*token)[quote->i] = ft_strdup(quote->end);
			if ((*token)[quote->i] == NULL)
				return (EXIT_FAILURE);
		}
		else
			ft_free_single_str(token, quote->i);
		return (EXIT_SUCCESS);
	}
	return (2);
}

/*
	The function special_start handles the case when 
	the token quote->start contains a special character
	(other than a quotation mark) that needs to be processed.

	* The function searches for the next occurrence of 
	the quotation mark (*quote->quote) starting from 
	the character following quote->start + 1. The result is
	stored in quote->end.

	If the length of quote->end is greater than 1,
	indicating that there are characters following the quotation mark,
	the function proceeds with further steps:
	{
		- The function duplicates quote->end by skipping the first character
		(since it represents the quotation mark itself) using ft_strdup.
		If the duplication fails (resulting in a NULL value),
		the function returns EXIT_FAILURE to indicate an error.
	}
	* If the length of quote->end is less than or equal to 1,
		indicating that it is empty or contains only the quotation mark,
		quote->end is set to NULL.
		
	* The function reallocates memory for quote->start to remove
	the characters following the quotation mark.
	The new size is determined by ft_strclen using quote->start + 1
	as the input string and *quote->quote + 2 as the set of characters
	to search for.
	If the reallocation fails (resulting in a NULL value), the function
	returns EXIT_FAILURE.

	* The memory allocated for the token at position (*token)[i] is freed
	using ft_free_str.

	* The token at position (*token)[i] is replaced
	with a duplicated version of quote->start using ft_strdup.
	If the duplication fails (resulting in a NULL value),
	the function returns EXIT_FAILURE.

	* If quote->end is not NULL, indicating that there are characters
	following the quotation mark, the function adds quote->end
	to the token array using ft_add_str_to_tab.

	* The function returns EXIT_SUCCESS to indicate successful execution.
*/

int	special_start(char ***token, t_quote *quote, int i)
{
	quote->end = ft_strchr(quote->start + 1, *quote->quote);
	if (ft_strlen(quote->end) > 1)
	{
		quote->end = ft_strdup(quote->end + 1);
		if (quote->end == NULL)
			return (EXIT_FAILURE);
	}
	else
		quote->end = NULL;
	quote->start = ft_realloc_str(quote->start,
			ft_strclen(quote->start + 1, *quote->quote + 2));
	if (quote->start == NULL)
		return (EXIT_FAILURE);
	ft_free_str(&(*token)[i]);
	(*token)[i] = ft_strdup(quote->start);
	if (quote->end != NULL)
		ft_add_str_to_tab(token, i, quote->end);
	return (EXIT_SUCCESS);
}

/*
	The functionis responsible for handling various cases when
	joining tokens.

	* If the quote parameter is NULL,
	the function returns EXIT_FAILURE to indicate an error.

	* The function checks if there is a quotation mark (*quote->quote)
	present after the first character in quote->start.
	If a quotation mark is found
	and the token at position (*token)[i] matches quote->start,
	it indicates that a special case needs to be handled.

	* If the special case condition is met,
	the function calls the special_start function to handle it.
	If special_start returns EXIT_FAILURE, the function returns
	EXIT_FAILURE as well.
	Otherwise, it returns EXIT_SUCCESS to indicate successful execution.

	* If the special case condition is not met,
	the function proceeds to check the length of quote->len.
	If it is greater than 0, indicating that there is a non-empty quote->start,
	the function calls the first_start function to handle the token joining process.
	The return value of first_start is checked, and if it is not 2,
	indicating a special case,
	the function returns the respective value
	(either EXIT_FAILURE or EXIT_SUCCESS).

	* If quote->len is 0, indicating an empty quote->start,
	the function calls the second_start function to handle the token
	joining process.
	The return value of second_start is checked, and if it is not 2,
	indicating a special case,
	the function returns the respective value
	(either EXIT_FAILURE or EXIT_SUCCESS).

	* If none of the above conditions are met,
	the function returns 2 to indicate that no special case was encountered.
*/

int	token_join_all(char ***token, t_quote *quote, int i)
{
	int	check;

	if (quote == NULL)
		return (EXIT_FAILURE);
	if ((ft_strchr(quote->start +1, *quote->quote) != NULL)
		&& ft_strcmp((*token)[i], quote->start) == 0)
	{
		if (special_start(token, quote, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	if (quote->len > 0)
	{
		check = first_start(token, quote);
		if (check != 2)
			return (check);
	}
	else
	{
		check = second_start(token, quote);
		if (check != 2)
			return (check);
	}
	return (2);
}

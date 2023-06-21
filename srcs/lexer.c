/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:59:10 by nassm             #+#    #+#             */
/*   Updated: 2023/06/21 14:54:33 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		ft_free_str(&tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

/*
	The functionis responsible for freeing the memory allocated 
	for the token arrays (token and resized) and resetting the lex token state.
*/
void	*free_token(char **token, char **resized)
{
	ft_free_tab(token);
	ft_free_tab(resized);
	reset_lex_token();
	return (NULL);
}

/*
	The functionis responsible for extracting 
	the next token from a given token string and updating the token pointer.

	* The function calls get_next_special to determine 
	the next special character in the tmp string and assigns it to next_spe.

	* The function enters a loop that checks if the current character 
	in tmp is equal to next_spe. 
	If so, it copies the character to next_token and increments the index i.

	* After the loop, the function calls ft_substr to create 
	a substring of *token starting from index i and assigns it to tmp.

	* It assigns tmp to *token, updating the token pointer 
	to the remaining substring.

	* Finally, the function returns the extracted next_token.
*/

char	*get_next_token(char **token)
{
	char	*next_token;
	char	*tmp;
	char	next_spe;
	int		i;

	tmp = *token;
	next_spe = get_next_special(tmp);
	next_token = ft_calloc(get_token_size(tmp, next_spe) + 1, \
		sizeof(*next_token));
	if (next_token == NULL)
		return (NULL);
	i = 0;
	if (*tmp == next_spe)
		while (*tmp && *tmp == next_spe)
			next_token[i++] = *tmp++;
	tmp = ft_substr(*token, i, ft_strlen(*token));
	if (*token == NULL)
		return (ft_free((void **)&next_token));
	free(*token);
	*token = tmp;
	return (next_token);
}

/*
	The functionis responsible for extracting a subtoken from an 
	array of tokens starting from a given index.

	* The function calls get_subtoken_count to determine 
	the number of subtokens starting from the current index *i in the token array 
	and assigns it to subtoken_count.

	* Within the loop, it performs the following checks:
	 - If subtoken_count is 1 and the current token contains 
	 a closing parenthesis ) and the length of the substring after 
	 the last occurrence of ) is not equal to 1, 
	 it calls get_end_subtoken to extract the end subtoken and returns its value.

	 * It appends a space character to the subtoken using ft_append. 
	 If the memory allocation fails (returns NULL), the function returns NULL.
	 
	 * If the current token contains an opening parenthesis ( or 
	 a closing parenthesis ), it decrements subtoken_count 
	 to keep track of the remaining subtokens.

	 * It increments the index *i to move to the next token.

	 * Once the loop is finished or if subtoken_count becomes zero,
	 indicating that all subtokens have been processed,
	 the function returns the subtoken string.
*/

char	*get_subtoken(char *token[], int *i)
{
	char	*subtoken;
	int		subtoken_count;

	subtoken = NULL;
	subtoken_count = get_subtoken_count(token, *i);
	while (token[*i] && subtoken_count)
	{
		if (subtoken_count == 1 && ft_strchr(token[*i], ')')
			&& ft_strlen(ft_strrchr(token[*i], ')')) != 1)
			return (get_end_subtoken(token, i, subtoken));
		subtoken = ft_append(&subtoken, " ");
		if (subtoken == NULL)
			return (NULL);
		if (ft_strchr(token[*i], '(') || ft_strchr(token[*i], ')'))
			subtoken_count--;
		(*i)++;
	}
	return (subtoken);
}

/*
	The functionis responsible for resizing and modifying an array of tokens.
	
	* The function enters a loop that iterates through the token array 
	using token[i[0]] as the condition.

	* Within the loop, it performs the following checks :
		- If the current token starts with an opening parenthesis (, 
	it calls get_subtoken.
		- If the current token is not a right special character 
	(as determined by token_is_right), it duplicates the current token 
	using ft_strdup and assigns it to resized[i[1]].
		- If the above conditions are not met, it calls get_next_token 
	to extract the next token from the current position in the token array 
	and assigns it to resized[i[1]].

	* After assigning the value to resized[i[1]], the function checks if it is NULL.
	If so, it returns NULL and frees the memory allocated for token and resized 
	using the free_token function.

	* The function then checks if the number of elements in resized 
	is equal to resized_size - 1. 
	If so, it reallocates memory for resized using 
	ft_realloc_str_arr, increasing resized_size by 10.

	* Once the loop is finished, the function frees the memory allocated 
	for token using ft_free_str_array and returns the modified resized array.
*/

char	**resize_token(char **token)
{
	char	**resized;
	size_t	resized_size;
	int		i[2];

	resized_size = 50;
	resized = ft_calloc(resized_size + 1, sizeof(*resized));
	if (resized == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (token[i[0]])
	{
		if (token[i[0]][0] == '(')
			resized[i[1]] = get_subtoken(token, &i[0]);
		else if (!token_is_right(token[i[0]]))
			resized[i[1]] = ft_strdup(token[i[0]++]);
		else
			resized[i[1]] = get_next_token(&token[i[0]]);
		if (resized[i[1]++] == NULL)
			return (free_token(token, resized));
		if ((size_t)i[1] == resized_size - 1)
			resized = ft_realloc_str_arr(resized, resized_size += 10);
	}
	ft_free_tab(token);
	return (resized);
}

int lexer(char  *rline)
{
	char    **token;
	int		exit_status;

	if (!valid_synthax_str(rline))
		return (exit_syntax_error());
	token = ft_split_set(rline, " \t\r\v\f\n");
	if (join_quote(token) == EXIT_FAILURE)
	{
		ft_free_str_array(&token);
		return (EXIT_FAILURE);
	}
	token = resize_token(token);
	if (token == NULL)
		return (EXIT_FAILURE);
	set_lex_token(token);
	if (!valid_syntax_token(token))
		return (exit_syntax_error());
	exit_status = parser(token);
	ft_free_tab(token);
	reset_lex_token();
	return (exit_status);
}

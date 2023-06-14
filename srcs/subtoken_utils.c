/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:04:04 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 17:08:20 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The functionis responsible for determining the number of subtokens 
	in an array of tokens starting from a given index.

	* It enters a loop that iterates through the token array starting 
	from the specified index i using token[i] as the condition.

	* Within the loop, it performs the following checks:
		- If the current token contains an opening parenthesis(,
		it increments the open_brack and count variables by one.
		- If the current token contains a closing parenthesis),
		it decrements the open_brack and increments the count by one.
		- If the open_brack variable becomes zero,
		indicating that all opening parentheses have been closed,
		it breaks out of the loop.

	* After the loop, the function returns the final value of count,
	which represents the total number of subtokens encountered.
*/

int	get_subtoken_count(char *token[], int i)
{
	int	count;
	int	open_brack;

	count = 0;
	open_brack = 0;
	while (token[i])
	{
		if (ft_strchr(token[i], '('))
		{
			open_brack++;
			count++;
		}
		else if (ft_strchr(token[i], ')'))
		{
			open_brack--;
			count++;
		}
		if (open_brack == 0)
			break ;
		i++;
	}
	return (count);
}

/*
	The function responsible for extracting the end portion 
	of a subtoken enclosed within parentheses.

	*  It calculates the length of the end portion by finding the difference 
	between the last occurrence of a closing parenthesis ) 
	in the current token (token[*i]) and the starting address of the token.

	* Using ft_substr, it creates a new string (tmp) that contains 
	the end portion of the token, including the closing parenthesis.

	* It appends the tmp string to the sub_token string using 
	ft_append, effectively concatenating the end portion to the existing
	sub_token string.

	* The tmp string is freed to avoid memory leaks.
	The tmp variable is assigned the current token (token[*i]).

	* The current token is updated using ft_substr to remove the extracted
	end portion, starting from the character immediately after the closing
	parenthesis.

	* Finally, the function returns the updated sub_token string
*/

char	*get_end_subtoken(char *token[], int *i, char *sub_token)
{
	char	*tmp;
	int		len;

	len = ft_strrchr(token[*i], ')') - token[*i];
	tmp = ft_substr(token[*i], 0, len + 1);
	sub_token = ft_append(&sub_token, tmp);
	free(tmp);
	tmp = token[*i];
	token[*i] = ft_substr(tmp, len +1, ft_strlen(token[*i]));
	free(tmp);
	return (sub_token);
}

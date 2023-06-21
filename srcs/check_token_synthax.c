/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_synthax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:50:37 by nassm             #+#    #+#             */
/*   Updated: 2023/06/19 16:00:37 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

/*
	The bool is_redirection(char *token) function takes a pointer
	 to a character string (char *token) as input and 
	 returns a Boolean value (true or false), 
	 indicating whether the token is a redirection or not.

	First, it checks if the length of the token is 2 characters. If it is, 
	it may indicate a special redirection like << or >>.
    If the token contains << or >>, the function returns true,
	 indicating that it is a redirection.

	If the length of the token is 1 character, it then checks if the character 
	is a redirection symbol like < or >.
    If the token contains < or >, the function returns true, 
	indicating that it is a redirection.

	If none of the previous conditions are met, the function returns false,
	indicating that the token is not a redirection.
*/

bool	is_redirection(char *token)
{
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, "<<") || ft_strstr(token, ">>"))
			return (true);
	}
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '<') || ft_strchr(token, '>'))
			return (true);
	}
	return (false);
}

/*
	This function checks various conditions to determine whether 
	a token represents a correct or valid special character.
	
	f the first character of the token is '(' and the token contains ')',
	the function returns true. This indicates that the token represents 
	a valid parentheses pair.

	If the length of the token is not equal to 2:
     * If the token contains any of the following combinations: "&&",
		"||", "<<", or ">>",
	the function returns false. This indicates that the token represents an
	invalid combination of special characters.
     * If the token contains the character '&', the function returns false.
		This indicates that the token represents an invalid occurrence of the '&'
		character.
		
	If the length of the token is not equal to 1:
     * If the token contains the character '<', but does not contain the
		combination "<<", the function returns false. This indicates that the
		token represents an invalid occurrence of the '<' character.
     * If the token contains the character '>', but does not contain the
		combination ">>", the function returns false.
		This indicates that the token represents an invalid occurrence of the
		'>' character.
     * If the token contains the character '|', but does not contain the
		combination "||", the function returns false.
		This indicates that the token represents an invalid occurrence of
		the '|' character.
*/

bool	is_correct_spe(char	*token)
{
	if (token[0] == '(' && ft_strchr(token, ')'))
		return (true);
	if (ft_strlen(token) != 2)
	{
		if (ft_strstr(token, "&&") || ft_strstr(token, "||")
			|| ft_strstr(token, "<<") || ft_strstr(token, ">>"))
			return (false);
		if (ft_strchr(token, '&'))
			return (false);
	}
	if (ft_strlen(token) != 1)
	{
		if ((ft_strchr(token, '<') && !ft_strstr(token, "<<"))
			|| (ft_strchr(token, '>') && !ft_strstr(token, ">>"))
			|| (ft_strchr(token, '|') && !ft_strstr(token, "||")))
			return (false);
	}
	return (true);
}

/*
	This function checks various conditions to determine whether 
	the combination of two tokens represents a correct or 
	valid usage of '|' .

	If the length of the current token is equal to 1 and it contains the
	'|' character, the function proceeds to further checks.
     * If the next token is NULL, indicating there is no subsequent token, 
	 the function returns false. This indicates an invalid occurrence 
	 of the '|' character without any command to pipe the output to.
     * If the length of the next token is 2:
       - If the next token contains "&&" or "||", indicating a logical 
	   operator, the function returns false. This indicates an invalid 
	   occurrence of the '|' character followed by a logical operator,
	    which is not allowed.
	
	If none of the above conditions are met, the function returns true.
*/

bool	is_correct_pipe(char *current, char *next)
{
	if (ft_strlen(current) == 1 && ft_strchr(current, '|'))
	{
		if (next == NULL)
			return (false);
		if (ft_strlen(next) == 2)
		{
			if (ft_strstr(next, "&&") || ft_strstr(next, "||"))
				return (false);
		}
	}
	return (true);
}

/*
	The function is used to determine whether a given token represents 
	a special character or combination of characters 
	based on a specified type.
*/

bool	is_special(char *token, int type)
{
	if (ft_strlen(token) == 1 && type == 0)
	{
		if ((ft_strchr(token, '<') && !ft_strstr(token, "<<"))
			|| (ft_strchr(token, '>') && !ft_strstr(token, ">>"))
			|| (ft_strchr(token, '|') && !ft_strstr(token, "||")))
			return (true);
	}
	if (ft_strlen(token) == 2 && type == 0)
	{
		if (ft_strstr(token, "<<") || ft_strstr(token, ">>"))
			return (true);
	}
	if (ft_strlen(token) == 2 && type == 3)
	{
		if (ft_strstr(token, "&&") || ft_strstr(token, "||"))
			return (true);
	}
	return (false);
}

/*
	The function iterates through each token in the token array.
	
	For each token, it performs the following checks:
	 * If the token fails the verif_is_token check,
		it proceeds with further checks.
	 * If the token is the first token (i == 0) or the next token is NULL,
		and the token is either "&&" or contains "||", the function returns false.
		This indicates an invalid occurrence of the logical operators.
	 * If the next token is NULL and the token is a redirection
		(checked using the is_redirection function), the function returns false.
		This indicates an invalid occurrence of a redirection without 
		a corresponding command.
	 * If the token fails the is_correct_spe check 
		(checks if it's a valid special character), the function returns false.
	 * If the combination of the current token and the next token fails 
		the is_correct_pipe check (checks the validity of the pipe character usage), 
		the function returns false.
	 * If the token contains both '(' and ')', and it is not the first token
		(i != 0) and the preceding token (token[i - 1]) is a special character, 
		the function returns false. This indicates an invalid occurrence 
		of parentheses after a special character.
	 * If all the tokens pass the checks, the function returns true,
		indicating that the syntax of the token sequence is valid.
*/

bool	valid_syntax_token(char	*token[])
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!verif_is_token(token[i]))
		{
			if (i == 0 || get_lexic_token()[i + 1] == NULL)
				if ((ft_strlen(token[i]) == 2 && ft_strstr(token[i], "&&"))
					|| ft_strstr(token[i], "||"))
					return (false);
			if (get_lexic_token()[i + 1] == NULL)
				if (is_redirection(token[i]))
					return (false);
			if (!is_correct_spe(token[i]))
				return (false);
			if (!is_correct_pipe(token[i], token[i + 1]))
				return (false);
			if (ft_strchr(token[i], '(') && ft_strchr(token[i], ')'))
				if (i != 0 && is_special(token[i - 1], 0))
					return (false);
		}
		i++;
	}
	return (true);
}

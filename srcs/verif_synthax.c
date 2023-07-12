/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:04:32 by nsalhi            #+#    #+#             */
/*   Updated: 2023/07/12 14:53:45 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is used to handle syntax errors.

	* The function displays an error message
	indicating the presence of an invalid syntax at a specific token.

	* The function calls set_err_code to set an error code
	representing the syntax error.
	This error code can be used for further error
	handling or program flow control.

	*It calls get_lexic_token to retrieve the lexic tokens,
	which likely contains the tokens of the input
	that resulted in the syntax error.

	* The function calls ft_free_split
	to free the memory allocated for the lexic tokens,
	ensuring proper memory management.
	
	* Finally, the function returns the EXIT_SYNTAX_ERROR constant,
	which is typically used as the exit code to indicate
	a syntax error in the minishell program.
*/

int	exit_syntax_error(void)
{
	write(2, "minishell: Invalid Syntax at token\n", 36);
	set_err_code(EXIT_SYNTAX_ERROR);
	ft_free_split(get_lexic_token());
	return (EXIT_SYNTAX_ERROR);
}

/*
	The function count_elem_char is used 
	to count the occurrences of a specific character (c)
	in a given string (rline).
	
	* it enters a loop that iterates
	through each character in the string rline.

	* Inside the loop, it checks if the current character is a single quote.
	If so, it skips all characters until the next single quote is encountered.
	This is done to ignore characters within single quotes.

	* Similarly, it checks if the current character is a double quote .
	If so, it skips all characters until the next double quote is encountered.
	This is done to ignore characters within double quotes.

	* If the current character is equal to the target character c,
	it increments the count variable to track the number of occurrences.

	* Finally, the function returns the total count of occurrences
	of the target character c in the string.
	
*/

int	count_elem_char(char *rline, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rline[i])
	{
		if (rline[i] == '\'')
			while (rline[++i] && rline[i] != '\'')
				;
		if (rline[i] == '\"')
			while (rline[++i] && rline[i] != '\"')
				;
		if (rline[i] == c)
			count++;
		if (rline[i])
			i++;
	}
	return (count);
}

/*
	The function is_correct_sub is used to determine if
	a given position i in a string rline corresponds to
	a correctly matched operator character ( & or | )
	for command sequencing.

	* The function enters a loop that iterates backwards
	from the given position i until it reaches the beginning
	of the string or finds a non-whitespace character.

	* Inside the loop,it checks if the current character
	at position i is a non-null character (rline[i])
	and if it is not a whitespace character.
	If this condition is true, it means that
	the character at position i is not a valid operator character
	for command sequencing, indicating an incorrect syntax.

	* If the loop completes without finding a
	non-whitespace character and i is greater than or equal to 0,
	it means that the position i does not have
	a valid operator character, and the function returns false.

	* If the loop finds a non-whitespace character before
	reaching the beginning of the string or if i is less than 0,
	it indicates that the position i has a correctly matched
	operator character for command sequencing,
	and the function returns true.
*/

bool	is_correct_sub(char *rline, int i)
{
	while (i > 0 && rline[i] && ft_isspace(rline[i]))
		i--;
	if (i >= 0 && (rline[i] != '&' && rline[i] != '|'))
		return (false);
	return (true);
}

/*
	The function is used to determine
	if there is an open bracket at or before
	the given position i in the string rline.

	* The function enters a loop that iterates backwards
	from the given position i until it reaches the beginning
	of the string or finds an open bracket

	* Inside the loop, it checks if the current character at
	position i is a non-null character (rline[i])
	and if it is not an open bracket ('(').
	If this condition is true, it means that the character
	at position i is not an open bracket,
	indicating that there is no open bracket at or before position i.

	* If the loop completes without finding an open bracket
	and i is greater than or equal to 0, it means that
	there is no open bracket at or before position i,
	and the function returns false.

	* If the loop finds an open bracket before
	reaching the beginning of the string or if i is less than 0,
	it indicates that there is an open bracket at or before position i,
	and the function returns true.
*/

bool	bracket_open(char *rline, int i)
{
	while (i > 0 && rline[i] != '(')
		i--;
	if (i >= 0 && rline[i] != '(')
		return (false);
	return (true);
}

/*
	The function valid_syntax_str is used to check
	the validity of a syntax string rline.
	It performs several checks to ensure that the syntax is valid.
	
	* The function checks if the number of open brackets ( is
	equal to the number of closing brackets (')').
	If they are not equal, it means that the brackets are not balanced,
	and the function returns false.

	* The function enters a loop that iterates through
	each character in the string rline.

	* Inside the loop, it checks for single quotes
	and double quotes and skips over the characters between them,
	as they are considered as string literals and not part of the syntax.
	
	* It checks if the current character is an open bracket.
	If so, it calls the function is_correct_sub to check if
	the preceding character is valid for a subshell.
	If it is not valid, the function returns false.

	* It checks if the current character is a closing bracket.
	If so, it calls the function bracket_open to check if there
	is an open bracket before it. If there is no open bracket,
	it means the brackets are not properly nested,
	and the function returns false.

	* It checks for the presence of ; and \.
	If any of these characters are found,
	it indicates an invalid syntax, and the function returns false

	* If the function completes the loop without encountering
	any syntax errors, it returns true,
	indicating that the syntax is valid.
*/

bool	valid_synthax_str(char	*rline)
{
	int	i;

	i = 0;
	if (count_elem_char(rline, '(') != count_elem_char(rline, ')'))
		return (false);
	while (rline[i])
	{
		if (rline[i] == '\'')
			while (rline[++i] && rline[i] != '\'')
				;
		if (rline[i] == '\"')
			while (rline[++i] && rline[i] != '\"')
				;
		if (rline[i] == '(')
			if (!is_correct_sub(rline, i - 1))
				return (false);
		if (rline[i] == ')')
			if (!bracket_open(rline, i))
				return (false);
		if (rline[i] == ';' || rline[i] == '\\')
			return (false);
		if (rline[i])
			i++;
	}
	return (true);
}

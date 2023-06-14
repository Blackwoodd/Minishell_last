/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:35:55 by nassm             #+#    #+#             */
/*   Updated: 2023/05/30 09:01:31 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../include/minishell.h"

/*
    The functionhecks whether a given token is a right token or not.

    * The function first checks if the token contains a single quote '
    or a double quote " character. If either of these characters is found,
    it returns false to indicate that the token is not a right token.
    
    * Next, the function checks if the token contains specific characters
    such as |, <, or >, but not in combination with certain strings
    like ||, <<, or >>. If such a combination is found and
    the length of the token is not equal to 1,
    it returns true to indicate that the token is a right token.

    * The function then checks if the token contains certain strings
    such as &&, <<, >>, or ||. If any of these strings are found and
    the length of the token is not equal to 2,
    it returns true to indicate that the token is a right token.

    * If none of the above conditions are met,
    the function returns false to indicate that
    the token is not a right token.
*/

bool    token_is_right(char *token)
{
    if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
        return (false);
    if ((ft_strchr(token, '|') && !ft_strstr(token, "||"))
            || (ft_strchr(token, '<') && !ft_strstr(token, "<<"))
            || (ft_strchr(token, '>') &&   !ft_strstr(token, ">>")))
        if (ft_strlen(token) != 1)
            return (true);
    if (ft_strstr(token, "&&") || ft_strstr(token, "<<")
            || ft_strstr(token, ">>") || ft_strstr(token, "||"))
        if (ft_strlen(token) != 2)
            return (true);
    return (false);
}

/*
    The function searches for the next special character in a given token.
    
    * The function iterates through each character in the token
    by incrementing the token pointer until it reaches the end
    of the string (indicated by a null terminator).

    * During each iteration,the function checks if 
    the current character is one of
    the special characters: |, <, >, ;.

    * If the current character is an & & 
    and the next character (at token + 1) is also an &,
    it is treated as the && operator.
    If a special character or the && operator is found,
    the function returns that character.

    * If no special character is found,
    the function returns the null character '\0'.
*/

char    get_next_special(char *token)
{
    while (*token)
    {
        if (*token == '|' || *token == '<'
                || *token == '>' || *token == ';')
            return (*token);
        if (*token == '&' && *(token +1) && *(token + 1) == '&')
            return (*token);
        token++;
    }
    return ('\0');
}

/*
    The function calculates the size of the next token
    in a given string based on
    the next special character (next_spe).

    * The function takes two parameters:
    the token string and the next_spe character that indicates
    the next special character.

    * It initializes a variable size to zero
    to keep track of the token size.

    * The function iterates through the characters 
    in the token string until it reaches the end (null terminator)
    or encounters the next_spe character.

    * During each iteration,
    it increments the size variable to count
    the number of characters in the token.

    * Once it reaches the next_spe character or
    the end of the string, the function stops iterating.

    * Finally, it returns the calculated size,
    which represents the size of the next token.
*/

size_t  get_token_size(char *token, char next_spe)
{
    size_t  size;

    size = 0;
    if (*token == next_spe)
    {
        while(*token && *token == next_spe)
        {
            token++;
            size++;
        }
    }
    else
    {
        while (*token && *token != next_spe)
        {
            token++;
            size++;
        }
    }
    return (size);
}

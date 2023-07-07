/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 09:56:51 by nassm             #+#    #+#             */
/*   Updated: 2023/07/07 15:25:32 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is used to replace a variable token in a string (lex_tok)
	with its corresponding value from the environment.

	* It calls the function get_env_var_val to retrieve the value of
	the environment variable var using the get_envar function.

	* It frees the memory allocated for the var parameter since it is
	no longer needed.

	* It allocates memory for the env_var string, considering the lengths
	of lex_tok and var_value, plus one additional byte
	for the null terminator.

	* The function then copies characters from lex_tok to env_var until
	it encounters a '$' character or reaches the end of the string.

	* It appends the var_value to env_var using the ft_append function,
	which concatenates the two strings.

	* It continues iterating over lex_tok until it reaches a non-alphabetic
	character or the end of the string, effectively skipping any subsequent
	characters that may be part of the modified variable name.

	* Finally, it appends the remaining portion of lex_tok to env_var and checks
	if the appending operation was successful.

	*It frees the memory allocated for var_value since it has been successfully
	appended to env_var.
	
	*The function returns the modified env_var string.
*/

char	*get_env_variable(char *lex_tok, char *var)
{
	char	*env_var;
	char	*var_value;
	int		i;

	var_value = get_env_var_val(get_envar(), var);
	free(var);
	if (var_value == NULL)
		return (NULL);
	env_var = ft_calloc(ft_strlen(lex_tok) + ft_strlen(var_value) +1, 1);
	if (env_var == NULL)
		return (NULL);
	i = -1;
	while (lex_tok[++i] && lex_tok[i] != '$')
		env_var[i] = lex_tok[i];
	env_var = ft_append(&env_var, var_value);
	if (env_var == NULL)
		return (var_value);
	while ((lex_tok[i]) == '$' || (lex_tok[i] && ft_isalpha(lex_tok[i])))
		i++;
	env_var = ft_append(&env_var, lex_tok + i);
	if (env_var == NULL)
		return (NULL);
	free(var_value);
	return (env_var);
}

/*
	The function extracts a variable name from a given string lex_tok
	that starts with a '$' character.

	* It allocates memory for the var string using the ft_calloc function.
	The allocated memory size is determined by the length of lex_buff plus
	one additional byte for the null terminator.

	* It initializes lex_buff with the memory address of the first 
	occurrence of the '$' character in lex_tok using the ft_strchr function
	and adds 1 to the address to skip the '$' character

	* The function enters a loop that continues as long as lex_buff is not NULL,
	*lex_buff is not a null character, and *lex_buff is an alphabetic character
	(checked using ft_isalpha).
	
		- Inside the loop, it assigns the value of *lex_buff to var[i],
		increments i, and advances lex_buff to the next character.
	
	* After the loop ends, the function returns the extracted var string.
*/

char	*get_var(char *lex_tok)
{
	char	*var;
	char	*lex_buff;
	int		i;

	lex_buff = lex_tok;
	var = ft_calloc(ft_strlen(lex_buff) + 1, sizeof(var));
	if (var == NULL)
		return (NULL);
	lex_buff = ft_strchr(lex_buff, '$') + 1;
	i = 0;
	while (lex_buff && *lex_buff && ft_isalpha(*lex_buff))
		var[i++] = *lex_buff++;
	return (var);
}

/*
	The functionnterprets environment variables within a given string
	lex_token.

	* It assigns the value of lex_token to result_token initially.

	*If the first character of lex_token is not a single quote ('),
	and the length of lex_token is greater than 1, and there is a '$'
	character present in lex_token, it enters the conditional block.

		- Inside the conditional block, it checks if lex_token contains
			"&?" characters using ft_strchr.
    
		- If "&?" characters are found, it frees the memory
			allocated for lex_token and returns the string representation
			of the error code using ft_itoa and get_err_code().
    
		- Otherwise, it assigns the result of get_env_var_variable(lex_token,
		get_var(lex_token)) to result_token. get_env_var_variable is
		a function that retrieves the value of an environment variable
		and replaces it in the lex_token string.
		It also frees the memory allocated for lex_token.
	
	* If lex_token does not contain any single quotes or double quotes, and it
		is equal to "*", it enters the conditional block.

		- Inside the conditional block, it frees the memory allocated for
		lex_token and returns the directory items using the function
		get_directory_items(). This function retrieves the items within the
		current directory and returns them as a string.

	* If none of the above conditions are met, it simply returns the result_token.
*/

char	*interpret_env_var(char *lex_token)
{
	char	*result_token;
	int		i;
	
	i = 0;
	result_token = lex_token;
	// while (lex_token[i] == '\'')
		// i++;
	if (lex_token[i] != '\016' && ft_strlen(lex_token) > 1
			&& ft_strchr(lex_token, '$') && !ft_strchr(lex_token, '\016'))
	{
		if (ft_strstr(lex_token, "$?"))
		{
			free(lex_token);
			return (ft_itoa(get_err_code()));
		}
		result_token = get_env_variable(lex_token, get_var(lex_token));
		free(lex_token);
		return (result_token);
	}
	if (!ft_strchr(lex_token, '\'') && !ft_strchr(lex_token, '\"')
			&& ft_strcmp(lex_token, "*\0") == 0)
	{
		free(lex_token);
		return (get_directory_items());
	}
	return (result_token);
}

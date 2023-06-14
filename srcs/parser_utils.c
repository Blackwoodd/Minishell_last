/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:40:26 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 16:33:43 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function s responsible for initializing the current t_par_tok token.
*/

int	init_current_pars_token(void)
{
	t_par_tok	**pars_token;
	t_iter		*iter;

	pars_token = get_pars_token();
	iter = get_iter();
	if (pars_token[iter[par]] != NULL)
		return (EXIT_SUCCESS);
	iter[cmd] = 0;
	iter[in] = 0;
	iter[out] = 0;
	pars_token[iter[par]] = ft_calloc(1 + 1, sizeof(*pars_token[iter[par]]));
	if (pars_token[iter[par]] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
	The function is responsible for freeing the memory allocated for
	t_par_tok tokens.
*/

int	free_pars_token(t_par_tok *pars_token[], int exit_code)
{
	int	i;

	i = 0;
	while (pars_token[i])
	{
		ft_free_str_array(&pars_token[i]->cmd);
		ft_free_str_array(&pars_token[i]->in);
		ft_free_str_array(&pars_token[i]->out);
		free(pars_token[i]);
		i++;
	}
	free(pars_token);
	return (exit_code);
}

/*
	The function is responsible for freeing the memory allocated
	for the parser-related data structures.
*/

int	free_parser(t_par_tok *pars_token[], t_iter *iter, int exit_status)
{
	free_pars_token(pars_token, 0);
	free(iter);
	reset_iter();
	reset_pars_token();
	return (exit_status);
}

/*
	The function is used to determine the size of the token array
	for the shell's syntax analysis.

	* The function get_stoken_size returns a size_t value representing
	the size of the token array.

	* Inside the loop, it checks the length of each lex_token[i] string.

	* If the length is 2, it further checks if the string contains specific
	substrings such as "&&", "||", or "<<" using ft_strstr.
	
	* If the length is 1, it checks if the string contains specific characters
	such as '|', '(', or ')', using ft_strchr.
	
	* Based on the conditions met, it increments the size variable accordingly.
	
	* After the loop, it adds 1 to the size to account for the null terminator
	in the token array.
*/

size_t	get_stoken_size(char *lex_token[])
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (lex_token[i])
	{
		if (ft_strlen(lex_token[i]) == 2)
		{
			if (ft_strstr(lex_token[i], "&&")
				|| ft_strstr(lex_token[i], "||")
				|| ft_strstr(lex_token[i], "<<"))
				size += 2;
		}
		if (ft_strlen(lex_token[i]) == 1)
		{
			if (ft_strchr(lex_token[i], '|')
				|| ft_strchr(lex_token[i], '(')
				|| ft_strchr(lex_token[i], ')'))
				size++;
		}
		i++;
	}
	size++;
	return (size);
}

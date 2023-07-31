/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:59:10 by nassm             #+#    #+#             */
/*   Updated: 2023/07/28 15:45:05 by nbechon          ###   ########.fr       */
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

void	*free_token(char **token, char **resized)
{
	ft_free_tab(token);
	ft_free_tab(resized);
	reset_lex_token();
	return (NULL);
}

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

bool	verif_create_var(char *token)
{
	int	i;
	int	len;

	len = ft_strlen(token);
	i = 0;
	while (token[i] && i < len)
	{
		if ((token[i] >= 'A' && token[i] <= 'Z')
			|| (token[i] >= 'a' && token[i] <= 'z')
			|| (token[i] >= '0' && token[i] <= '9'))
			i++;
		else
			break ;
	}
	if (token[i] != '=')
		return (false);
	else
		i++;
	if (token[i] != '\0' && token[i] != ' ' && token[i] != '\t')
		return (true);
	else
		return (false);
}

void	implem_var(char *token)
{
	t_env	*envar;
	int		i;

	envar = get_envar();
	i = ft_str_arr_len(envar->tmp_var);
	ft_add_str_to_tab(&envar->tmp_var, i + 1, token);
}

void	create_var(char **token)
{
	int	i;
	int	len;
	int	count;

	i = 0;
	count = 0;
	len = ft_str_arr_len(token);
	while (token[i] && i < len)
	{
		if (verif_create_var(token[i]))
		{
			implem_var(token[i]);
			if (i == 0)
				ft_free_single_str(&token, i);
			count = 1;
		}
		i++;
	}
	if (i == 1 && count == 1)
	{
		ft_free_str_array(&token);
		core();
	}
}

int lexer(char *rline)
{
	char	**token;
	int		exit_status;

	if (!valid_synthax_str(rline))
		return (exit_syntax_error());
	token = ft_split_set(rline, " \t\r\v\f\n");
	// int k = 0;
	// while (token[k])
	// 	printf ("%s\n", token[k++]);
	// exit (0);
	if (join_quote(token) == EXIT_FAILURE)
	{
		ft_free_tab(token);
		core();
	}
	token = resize_token(token);
	if (token == NULL)
		return (EXIT_FAILURE);
	set_lex_token(token);
	create_var(token);
	if (!valid_syntax_token(token))
		return (exit_syntax_error());
	exit_status = parser(token);
	reset_lex_token();
	return (exit_status);
}

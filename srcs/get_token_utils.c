/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:55:46 by nassm             #+#    #+#             */
/*   Updated: 2023/05/28 15:29:41 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	This function determines whether a token contains single quotes 
	or double quotes.
*/

bool	verif_is_token(char *token)
{
	if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
		return (true);
	return (false);
}

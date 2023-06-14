/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tok_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:01:00 by nassm             #+#    #+#             */
/*   Updated: 2023/06/07 11:42:38 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
    Thefunction is responsible for managing a static array of t_exp_tok pointers.

    *The function takes two parameters: exp_toks (an array of t_exp_tok pointers)
    and reset (a boolean flag).
    
    *If exp_toks is NULL and reset is false, the function returns the current
    value of the static array static_exp_toks.
    
    *If reset is true, the function resets the static array static_exp_toks
    to NULL and returns NULL.
    
    *If exp_toks is not NULL, the function assigns the value of
    exp_toks to the static array static_exp_toks and returns static_exp_toks.
*/

static t_exp_tok    **get_ex_tokens(t_exp_tok *exp_toks[], bool reset)
{
    static t_exp_tok    **static_exp_toks = NULL;

    if (exp_toks == NULL && !reset)
        return (static_exp_toks);
    if (reset)
    {
        static_exp_toks = NULL;
        return (NULL);
    }
    static_exp_toks = exp_toks;
    return (static_exp_toks);
}

t_exp_tok   **get_exp_toks(void)
{
    return(get_ex_tokens(NULL, false));
}

void    set_exp_toks(t_exp_tok *exp_tok[])
{
    get_ex_tokens(exp_tok, false);
}

void    reset_exp_toks(void)
{
    get_ex_tokens(NULL, true);
}
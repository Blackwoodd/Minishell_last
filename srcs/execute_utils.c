/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:30:43 by nassm             #+#    #+#             */
/*   Updated: 2023/07/06 14:51:47 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_builtin_redirection(t_exp_tok *exp_tok, t_exp_tok **exp_toks)
{
	int	exit_status;
	int	pipes_save[2];

	if (exp_tok->in != STDIN_FILENO)
	{
		pipes_save[STDIN_FILENO] = dup(STDIN_FILENO);
		if (pipes_save[STDIN_FILENO] == -1)
			return (ft_perror(EXIT_FAILURE, "Pipe error"));
		if (dup2(exp_tok->in, STDIN_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "Pipe_Error"));
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		pipes_save[STDOUT_FILENO] = dup(STDOUT_FILENO);
		if (pipes_save[STDOUT_FILENO] == -1)
			return (ft_perror(EXIT_FAILURE, "dup error"));
		if (dup2(exp_tok->out, STDOUT_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup2 error"));
	}
	if (exp_tok->is_pipe == true)
		exit_status = execute_builtin_child(exp_tok);
	else
		exit_status = execute_builtin(exp_tok, exp_toks);
	exbuiltin_reset_fd(exp_tok, pipes_save);
	return (exit_status);
}

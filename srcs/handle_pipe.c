/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:13:47 by nassm             #+#    #+#             */
/*   Updated: 2023/07/26 16:44:04 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_not_pipe(int last_pipe_out)
{
	if (last_pipe_out != 0 && last_pipe_out != 1)
	{
		close(last_pipe_out);
		ft_putstr_fd("Errror opening pipe\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	pipe_t_end_pipe(int *last_pipe_out, t_exp_tok *exp_tok)
{
	if (*last_pipe_out == 0)
	{
		ft_putstr_fd("Error, opening pipe \n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exp_tok->in = *last_pipe_out;
	close(*last_pipe_out);
	*last_pipe_out = 1;
	return (EXIT_SUCCESS);
}

static int	pipe_t_start_pipe(int *last_pipe_out, t_exp_tok *exp_tok)
{
	int	pipes[2];

	if (pipe(pipes) != 0)
		return (ft_perror(EXIT_FAILURE, "pipe error)"));
	*last_pipe_out = pipes[0];
	exp_tok->out = pipes[1];
	exp_tok->fd_to_close = pipes[0];
	return (EXIT_SUCCESS);
}

static int	pipe_t_middle_pipe(int *last_pipe_out, t_exp_tok *exp_tok)
{
	int	pipes[2];

	if (*last_pipe_out == 1)
	{
		ft_putstr_fd("Errror opening pipe\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exp_tok->in = *last_pipe_out;
	*last_pipe_out = 0;
	if (pipe(pipes) != 0)
		return (ft_perror(EXIT_FAILURE, "pipe error"));
	*last_pipe_out = pipes[0];
	exp_tok->out = pipes[1];
	exp_tok->fd_to_close = pipes[0];

	*last_pipe_out = pipes[0];
	if (exp_tok->out == 1)
		exp_tok->out = pipes[1];
	else
		close(pipes[1]);
	return (EXIT_SUCCESS);
}

int	handle_pipes(t_exp_tok *exp_tok, t_pipe_type pipe_type)
{
	static int	last_pipe_out;

	exp_tok->fd_to_close = -1;
	if (pipe_type == NOT_PIPE)
		return (is_not_pipe(last_pipe_out));
	else if (pipe_type == START_PIPE)
		return (pipe_t_start_pipe(&last_pipe_out, exp_tok));
	else if (pipe_type == MIDDLE_PIPE)
		return (pipe_t_middle_pipe(&last_pipe_out, exp_tok));
	else if (pipe_type == END_PIPE)
		return (pipe_t_end_pipe(&last_pipe_out, exp_tok));
	return (EXIT_SUCCESS);
}


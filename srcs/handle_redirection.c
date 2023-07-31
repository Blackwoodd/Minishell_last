/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:56:51 by nassm             #+#    #+#             */
/*   Updated: 2023/07/27 16:07:49 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_in(t_par_tok *par_token, t_exp_tok *exp_tok)
{
	int		i;

	if (par_token->in_redir == IS_IN)
	{
		i = 0;
		while (par_token->in[i])
		{
			if (exp_tok->in != 0)
				close(exp_tok->in);
			exp_tok->in = open(par_token->in[i], O_RDONLY);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

static int	open_out(t_par_tok *par_token, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	while (par_token->out_redir == IS_OUT
		|| par_token->out_redir == IS_OUT_APPEND)
	{
		if (par_token->out_redir == IS_OUT
			&& ft_strcmp(par_token->out[i++], ">") == 0)
			fd = open(par_token->out[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (par_token->out_redir == IS_OUT_APPEND
			&& ft_strcmp(par_token->out[i++], ">>") == 0)
			fd = open(par_token->out[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (ft_perror(EXIT_FAILURE, "open error"));
		if (par_token->out[i + 1] == NULL)
			break ;
		if (fd != 0 && fd != 1)
			close(fd);
		i++;
	}
	exp_tok->out = fd;
	return (EXIT_SUCCESS);
}

// int	handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok, t_pipe_type pipe_type)
// {
// 	int	exit_status;

// 	if (open_in(par_tok, exp_tok) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (open_out(par_tok, exp_tok) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (handle_pipes(exp_tok, pipe_type) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (par_tok->redir_type == IS_PIPE)
// 		exp_tok->is_pipe = true;
// 	else
// 		exp_tok->is_pipe = false;
// 	exit_status = ft_execute(exp_tok, NULL);
// 	if (exp_tok->in != STDIN_FILENO)
// 		close(exp_tok->in);
// 	if (exp_tok->out != STDOUT_FILENO)
// 		close (exp_tok->out);
// 	return (exit_status);
// }

int	handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok, t_pipe_type pipe_type)
{
	int	exit_status;
	int	dev_null;
	int	saved_stderr;
	int	saved_stdout;

	dev_null = open("/dev/null", O_WRONLY);
	if (dev_null == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	dup2(dev_null, STDOUT_FILENO);
	dup2(dev_null, STDERR_FILENO);
	close(dev_null);
	if (open_in(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (open_out(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_pipes(exp_tok, pipe_type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (par_tok->redir_type == IS_PIPE)
		exp_tok->is_pipe = true;
	else
		exp_tok->is_pipe = false;
	exit_status = ft_execute(exp_tok, NULL);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stderr);
	close(saved_stdout);
	if (exp_tok->in != STDIN_FILENO)
		close(exp_tok->in);
	if (exp_tok->out != STDOUT_FILENO)
		close(exp_tok->out);
	return (exit_status);
}
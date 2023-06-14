/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:24:37 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 17:19:26 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function searches for the <<" element in par_tok->in and returns
	the corresponding heredoc content. If it doesn't find the <<" element,
	it returns NULL.
*/

static char	*get_heredoc(t_par_tok *par_tok)
{
	int	i;

	i = 0;
	while (par_tok->in[i])
	{
		if (ft_strcmp(par_tok->in[i], "<<") == 0)
			return (par_tok->in[i + 1]);
		i++;
	}
	return (NULL);
}

static int	exit_close_fds(int fd1, int fd2, int exit_status)
{
	if (fd1 != -1)
		close(fd1);
	if (fd1 != -1)
		close(fd2);
	return (exit_status);
}

/*
	The function wait_for_heredoc_help is a helper function that takes
	a t_exp_tok pointer exp_tok as input.

	* It checks if exp_tok->cmd is NULL and exp_tok->out is not
	equal to STDOUT_FILENO.
	
	* If the conditions are met, it closes the file descriptor exp_tok->out.
	
	* It sets exp_tok->out to STDOUT_FILENO.
*/

static void	wait_for_heredoc_help(t_exp_tok *exp_tok)
{
	if (exp_tok->cmd == NULL && exp_tok->out != STDOUT_FILENO)
	{
		close(exp_tok->out);
		exp_tok->out = STDOUT_FILENO;
	}
}

/*
	the  function sets up a pipe, reads input until the heredoc string
	is entered, and writes the input to the pipe. It then performs
	necessary cleanup and returns a success code.

	*It declares an integer array end with two elements.

	*It calls the pipe function to create a pipe, and stores
	the file descriptors in the end array.
	
	*It sets exp_tok->in to end[0], which is the read end of the pipe.

	* It calls the get_heredoc function to retrieve the heredoc string
	from par_tok and assigns it to the heredoc variable.

	* If heredoc is NULL, indicating that the heredoc string could not
	be obtained, it returns an error code.

	* It enters a loop that reads input using the readline function,
	storing the input in the buf variable.

	*If buf is NULL, indicating an error or end of input,
	it closes the write end of the pipe and returns a success code.

	*If the input in buf is equal to the
	heredoc string, the loop is exited.

	*It writes the content of buf followed by a newline
	character to the write end of the pipe using ft_fprintf.

	*It frees the memory allocated for buf.

	*After the loop, it frees the memory allocated
	for buf again to ensure proper cleanup.

	*It closes the write end of the pipe.

	*It calls the wait_for_heredoc_help function to perform
	additional operations on exp_tok.

	*It returns a success code.
*/

int	wait_for_heredoc(t_par_tok *par_tok, t_exp_tok *exp_tok,
		char *buff, char *heredoc)
{
	int		end[2];

	if (pipe(end) == -1)
		return (ft_perror(EXIT_FAILURE, "pipe error"));
	exp_tok->in = end[0];
	heredoc = get_heredoc(par_tok);
	if (heredoc == NULL)
		return (exit_close_fds(end[0], end[1], EXIT_FAILURE));
	while (true)
	{
		buff = readline("> ");
		if (buff == NULL)
			return (exit_close_fds(end[1], -1, EXIT_SUCCESS));
		if (ft_strcmp(buff, heredoc) == 0)
			break ;
		ft_fprintf(end[1], "%s\n", buff);
		free(buff);
	}
	free(buff);
	close(end[1]);
	wait_for_heredoc_help(exp_tok);
	return (EXIT_SUCCESS);
}

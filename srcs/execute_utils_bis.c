/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:28:39 by nassm             #+#    #+#             */
/*   Updated: 2023/07/27 16:14:56 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_child(t_exp_tok *exp_tok, char *abs_cmd_path, int status)
{
	if (exp_tok->fd_to_close != -1)
	{
		close(exp_tok->fd_to_close);
	}

	if (exp_tok->in != STDIN_FILENO)
	{
		dup2(exp_tok->in, STDIN_FILENO);
		close(exp_tok->in);
	}

	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(exp_tok->out, STDOUT_FILENO);
		close(exp_tok->out);
	}
	status = execve(abs_cmd_path, exp_tok->cmd, get_envar()->env_var);
	perror(NULL);
	return (status);
}

int	execute_builtin(t_exp_tok *exp_tok, t_exp_tok **exp_toks)
{
	if (ft_strcmp(exp_tok->cmd[0], "echo") == 0)
		return (commande_echo(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "export") == 0)
		return (commande_export(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "env") == 0)
		return (commande_env(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "cd") == 0)
		return (commande_cd(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "pwd") == 0)
		return (commande_pwd(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "unset") == 0)
		return (commande_unset(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "exit") == 0)
		return (commande_exit(exp_tok->cmd, exp_tok, exp_toks));
	return (EXIT_FAILURE);
}

int	execute_builtin_child(t_exp_tok *exp_tok)
{
	pid_t	pid;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		exit_status = execute_builtin(exp_tok, NULL);
		exit(exit_status);
	}
	else
    {
        waitpid(pid, &exit_status, 0); // Attente du processus fils pour obtenir le statut de sortie correct.
    }
	return (exit_status);
}

int	exbuiltin_reset_fd(t_exp_tok *exp_tok, int pipes_save[2])
{
	if (exp_tok->in != STDIN_FILENO)
	{
		dup2(pipes_save[STDIN_FILENO], STDIN_FILENO);
		close(pipes_save[STDIN_FILENO]);
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(pipes_save[STDOUT_FILENO], STDOUT_FILENO);
		close(pipes_save[STDOUT_FILENO]);
	}
	return (EXIT_SUCCESS);
}

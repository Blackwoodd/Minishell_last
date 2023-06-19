/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:41:42 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/14 17:19:01 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd(char *cmd)
{
	char	**path_splitted;
	char	*abs_cmd_path;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (init_path(&path_splitted) == EXIT_FAILURE)
		return (NULL);
	i = 0;
	while (path_splitted[i])
	{
		abs_cmd_path = get_abs_cmd_path(path_splitted[i], cmd);
		if (abs_cmd_path == NULL)
			return (NULL);
		if (access(abs_cmd_path, F_OK) == 0)
		{
			ft_free_split(path_splitted);
			return (abs_cmd_path);
		}
		ft_free((void *)&abs_cmd_path);
		i++;
	}
	ft_free_split(path_splitted);
	return (NULL);
}

void	cmd_not_found(t_exp_tok *exp_tok)
{
	char	*str;

	str = ft_strjoin(exp_tok->cmd[0], ": Command not found");
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(str);
}

int	exec_cmd(t_exp_tok *exp_tok, char *abs_cmd_path)
{
	pid_t	pid;
	int		estatus;

	estatus = 0;
	cmd_signal();
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
		return (execute_child(exp_tok, abs_cmd_path, estatus));
	waitpid(pid, &estatus, 0);
	global_signal();
	return (WEXITSTATUS(estatus));
}

int	ft_execute(t_exp_tok *exp_tok)
{
	int		exit_status;
	char	*abs_cmd_path;

	if (exp_tok == NULL)
		return (EXIT_SUCCESS);
	if (clean_quote_exp_tok_cmd(exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_builtin(exp_tok->cmd[0]))
		return (handle_builtin_redirection(exp_tok));
	abs_cmd_path = get_cmd(exp_tok->cmd[0]);
	if (abs_cmd_path == NULL || ft_strlen(exp_tok->cmd[0]) == 0)
	{
		free(abs_cmd_path);
		cmd_not_found(exp_tok);
		return (EXIT_CMD_NOT_FOUND);
	}
	exit_status = exec_cmd(exp_tok, abs_cmd_path);
	free(abs_cmd_path);
	return (exit_status);
}

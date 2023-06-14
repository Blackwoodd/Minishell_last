/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:45:10 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 16:42:02 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	this function is used to remove the outer quotes from a command
	string if they exist.
*/

char	*clean_cmd(char *cmd)
{
	char	*ok_cmd;
	int		cmd_len;
	int		i;
	int		j;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] != '\'' && cmd[0] != '\"')
		return (cmd);
	if (cmd[cmd_len - 1] != cmd[0])
		return (cmd);
	ok_cmd = ft_calloc(cmd_len +1, sizeof(*ok_cmd));
	if (ok_cmd == NULL)
	{
		free(cmd);
		return (NULL);
	}
	i = 1;
	j = 0;
	while (i < cmd_len - 1)
		ok_cmd[j++] = cmd[i++];
	free(cmd);
	return (ok_cmd);
}

/*
	This function cleans the outer quotes from each command in
	the exp_tok->cmd array, ensuring that the commands are properly formatted 
*/
int	clean_quote_exp_tok_cmd(t_exp_tok *exp_tok)
{
	int	i;

	i = 0;
	while (exp_tok && exp_tok->cmd && exp_tok->cmd[i])
	{
		exp_tok->cmd[i] = clean_cmd(exp_tok->cmd[i]);
		if (exp_tok->cmd[i] == NULL)
		{
			ft_free_split(exp_tok->cmd);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

int	init_path(char **path_splitted[])
{
	char	*path;

	path = get_env_var_val(get_envar(), "PATH");
	if (path == NULL)
		return (EXIT_FAILURE);
	*path_splitted = ft_split(path, ':');
	free(path);
	if (*path_splitted == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*get_abs_cmd_path(char *path_splitted, char *cmd)
{
	char	*abs_cmd_path;

	abs_cmd_path = ft_strjoin(path_splitted, "/");
	if (abs_cmd_path == NULL)
		return (NULL);
	abs_cmd_path = ft_append(&abs_cmd_path, cmd);
	if (abs_cmd_path == NULL)
		return (NULL);
	return (abs_cmd_path);
}

// char	*get_cmd(char *cmd)
// {
// 	char	**path_splitted;
// 	char	*abs_cmd_path;
// 	int		i;

// 	if (access(cmd, F_OK) == 0)
// 		return (ft_strdup(cmd));
// 	if (init_path(&path_splitted) == EXIT_FAILURE)
// 		return (NULL);
// 	i = 0;
// 	while (path_splitted[i])
// 	{
// 		abs_cmd_path = get_abs_cmd_path(path_splitted[i], cmd);
// 		if (abs_cmd_path == NULL)
// 			return (NULL);
// 		if (access(abs_cmd_path, F_OK) == 0)
// 		{
// 			ft_free_split(path_splitted);
// 			return (abs_cmd_path);
// 		}
// 		ft_free((void *)&abs_cmd_path);
// 		i++;
// 	}
// 	ft_free_split(path_splitted);
// 	return (NULL);
// }

// void	cmd_not_found(t_exp_tok *exp_tok)
// {
// 	char	*str;

// 	str = ft_strjoin(exp_tok->cmd[0], ": Command not found");
// 	write(2, str, ft_strlen(str));
// 	write(2, "\n", 1);
// 	free(str);
// }

// int	exec_cmd(t_exp_tok *exp_tok, char *abs_cmd_path)
// {
// 	pid_t	pid;
// 	int		estatus;

// 	estatus = 0;
// 	cmd_signal();
// 	pid = fork();
// 	if (pid < 0)
// 		return (EXIT_FAILURE);
// 	if (pid == 0)
// 		return (execute_child(exp_tok, abs_cmd_path, estatus));
// 	waitpid(pid, &estatus, 0);
// 	global_signal();
// 	return (WEXITSTATUS(estatus));
// }

// int ft_execute(t_exp_tok *exp_tok)
// {
// 	int		exit_status;
// 	char	*abs_cmd_path;

// 	if (exp_tok == NULL)
// 		return (EXIT_SUCCESS);
// 	if (clean_quote_exp_tok_cmd(exp_tok) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (is_builtin(exp_tok->cmd[0]))
// 		return (handle_builtin_redirection(exp_tok));
// 	abs_cmd_path = get_cmd(exp_tok->cmd[0]);
// 	if (abs_cmd_path == NULL || ft_strlen(exp_tok->cmd[0]) == 0)
// 	{
// 		free(abs_cmd_path);
// 		cmd_not_found(exp_tok);
// 		return (EXIT_CMD_NOT_FOUND);
// 	}
// 	exit_status = exec_cmd(exp_tok, abs_cmd_path);
// 	free(abs_cmd_path);
// 	return (exit_status);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:45:10 by nassm             #+#    #+#             */
/*   Updated: 2023/07/12 15:06:00 by nbechon          ###   ########.fr       */
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

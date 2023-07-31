/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:01:00 by nassm             #+#    #+#             */
/*   Updated: 2023/07/27 16:09:47 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute_subshell(t_exp_tok *exp_tok)
{
	pid_t	pid;
	int		status;
	char	*cutted_cmd;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		cutted_cmd = ft_substr(exp_tok->cmd[0], 1,
				ft_strrchr(exp_tok->cmd[0], ')') - exp_tok->cmd[0] - 1);
		if (cutted_cmd == NULL)
			return (EXIT_FAILURE);
		status = lexer(cutted_cmd);
		free(cutted_cmd);
		exit(get_err_code());
	}
	set_err_code(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

static bool	is_redir(t_par_tok *par_tok)
{
	return (par_tok->redir_type != NONE);
}

static int	process_express_tokens(t_exp_tok *exp_toks[], t_par_tok *par_toks[])
{
	int	i;
	int	status;

	i = 0;
	while (exp_toks[i] && par_toks[i])
	{
		if (par_toks[i]->type == and || par_toks[i]->type == or)
		{
			if ((par_toks[i]->type == and && get_err_code() != EXIT_SUCCESS)
				|| (par_toks[i]->type == or && get_err_code() == EXIT_SUCCESS))
				i++;
			reinterprete_env_vars(&par_toks[i + 1], &exp_toks[i + 1]);
		}
		else if (is_redir(par_toks[i]))
		{
			set_err_code(handle_redir(par_toks[i], exp_toks[i],
					set_pipe_type(par_toks, i)));
		}
		else if (exp_toks[i]->cmd != NULL)
		{
			set_err_code(ft_execute(exp_toks[i], exp_toks));
		}
		i++;
	}
	i = 0;
	while (exp_toks[i])
	{
		if (exp_toks[i]->in != 0)
			close(exp_toks[i]->in);
		if (exp_toks[i]->out != 1)
			close(exp_toks[i]->out);
		i++;
	}
	i = 0;
	while (exp_toks[i])
	{
		waitpid(exp_toks[i]->pid, &status, 0);
		i++;
	}
	return (EXIT_SUCCESS);
}

// void afficher_exp_toks(t_exp_tok** exp_toks) {
//     if (exp_toks == NULL) {
//         printf("Le tableau d'expressions est NULL.\n");
//         return;
//     }

//     printf("Valeurs des tokens d'expression :\n");
//     for (int i = 0; exp_toks[i] != NULL; i++) {
//         printf("Token %d : cmd: %s, in: %d, out: %d, is_pipe: %s, fd_to_close: %d, pid: %d, is_builtin_cmd: %s\n",
//                i,
//                exp_toks[i]->cmd[0],
//                exp_toks[i]->in,
//                exp_toks[i]->out,
//                exp_toks[i]->is_pipe ? "true" : "false",
//                exp_toks[i]->fd_to_close,
//                exp_toks[i]->pid,
//                exp_toks[i]->is_builtin_cmd ? "true" : "false"
//         );
//     }
// }

int	expander(t_par_tok *pars_token[])
{
	t_exp_tok	**exp_tok;

	if (get_tokens(pars_token) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exp_tok = get_exp_toks();
	// afficher_exp_toks(exp_tok);
	return (free_exp_toks(exp_tok,
			process_express_tokens(exp_tok, pars_token)));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:01:00 by nassm             #+#    #+#             */
/*   Updated: 2023/07/04 15:45:44 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function s responsible for executing a subshell command within
	the context of the current process.
	
	*It starts by creating a child process using fork().
	If the creation of the child process fails (pid < 0),
	it returns EXIT_FAILURE.
    
	*Inside the child process (pid == 0), it prepares the command to be
	executed within the subshell. It extracts the substring of the first command
	(exp_tok->cmd[0]) excluding the opening and closing parentheses.
	This extracted command is stored in the cutted_cmd variable.
    
	*If the extraction of the subshell command fails (cutted_cmd == NULL),
	it returns EXIT_FAILURE.
    
	*The cutted_cmd is then passed to the lexer function to tokenize
	and process it.
    
	*After executing the subshell command, the child process exits with
	the error code retrieved from get_err_code().
    
	*The parent process waits for the child process to complete using waitpid.
	The status of the child process is stored in the status variable.
    
	*The error code is set to the value returned by the
	child process (WEXITSTATUS(status)).
    
	*The function returns the same error code.
*/

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
	waitpid(pid, &status, 0);
	set_err_code(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

static bool	is_redir(t_par_tok *par_tok)
{
	if (par_tok->redir_type[is_in] || par_tok->redir_type[is_in_heredoc] \
	|| par_tok->redir_type[is_out] || par_tok->redir_type[is_out_append] \
	|| par_tok->redir_type[is_pipe])
		return (true);
	return (false);
}

/*
	The function process_express_tokens takes two arrays of tokens,
	exp_toks[] and par_toks[], and processes them accordingly.

	*It enters a loop that iterates as long as there are both exp_toks
	and par_toks at index i.
	
	*Inside the loop, it checks the type of the current par_toks[i]:

    	-If the type is and or or, it evaluates the condition based on
		the previous error code (get_err_code()). If the condition is met,
		it increments i and reinterprets environment variables
		for the subsequent tokens.
    
		-If the type is subshell, it executes the subshell by calling
		the execute_subshell function and sets the error code using set_err_code.
    	
		-If the token is a redirection token, it handles the redirection by
		calling the handle_redir function and sets the error code using set_err_code.
		It also determines the pipe type using set_pipe_type.
    
		-If the token represents a command, it executes the command by
		calling the ft_execute function and sets the error code using set_err_code.

	*After processing each token, it increments i to move to the next token.

	*Finally, it returns EXIT_SUCCESS to indicate the successful execution of
	the function.
*/

static int	process_express_tokens(t_exp_tok *exp_toks[], t_par_tok *par_toks[])
{
	int	i;

	i = 0;
	while (exp_toks[i] && par_toks[i])
	{
		if (par_toks[i]->type == and || par_toks[i]->type == or)
		{
			if ((par_toks[i]->type == and && get_err_code() != EXIT_SUCCESS) \
			|| (par_toks[i]->type == or && get_err_code() == EXIT_SUCCESS))
				i++;
			reinterprete_env_vars(&par_toks[i + 1], &exp_toks[i + 1]);
		}
		else if (par_toks[i]->type == subshell)
			set_err_code(execute_subshell(exp_toks[i]));
		else if (is_redir(par_toks[i]))
			set_err_code(handle_redir(par_toks[i], exp_toks[i], \
			set_pipe_type(par_toks, i)));
		else if (exp_toks[i]->cmd != NULL)
			set_err_code(ft_execute(exp_toks[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
	The function takes an array of parsed tokens pars_token[]
	and performs token expansion and processing.

	*It checks if tokenization of the input string (stored in pars_token)
	is successful by calling the get_tokens function. If the tokenization fails,
	it returns EXIT_FAILURE.
    
	*It retrieves the expanded tokens using the get_exp_toks function and assigns
	them to the variable exp_tok.
    
	*It calls the process_express_tokens function, passing the exp_tok and
	pars_token arrays as arguments, to process and execute the expanded tokens.
    
	*It calls the free_exp_toks function to free the memory allocated for
	the expanded tokens (exp_tok) and passes the result of
	process_express_tokens as an argument.
    
	*Finally, it returns the result of free_exp_toks,
	which indicates the success or failure of the token expansion and processing.
*/

int	expander(t_par_tok *pars_token[])
{
	t_exp_tok	**exp_tok;

	if (get_tokens(pars_token) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exp_tok = get_exp_toks();
	return (free_exp_toks(exp_tok,
			process_express_tokens(exp_tok, pars_token)));
}

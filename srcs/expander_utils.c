/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:20:01 by nassm             #+#    #+#             */
/*   Updated: 2023/06/07 11:39:58 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function initializes a t_exp_tok struct.

	*It allocates memory for a single t_exp_tok struct using malloc and
	assigns the address to the double pointer exp_tok.

	*If the memory allocation fails (i.e., *exp_tok is NULL),
	it returns EXIT_FAILURE to indicate an error.

	*It sets the cmd member of the t_exp_tok struct to NULL,
	indicating that there is no associated command.

	*It sets the in member of the t_exp_tok struct to 0,
	representing the file descriptor for input (stdin).

	*It sets the out member of the t_exp_tok struct to 1,
	representing the file descriptor for output (stdout).

	*It sets the is_pipe member of the t_exp_tok struct to false,
	indicating that it is not part of a pipe.
*/

int init(t_exp_tok **exp_tok)
{
	*exp_tok = malloc(sizeof(**exp_tok));
	if (*exp_tok == NULL)
		return (EXIT_FAILURE);
	(*exp_tok)->cmd = NULL;
	(*exp_tok)->in = 0;
	(*exp_tok)->out = 1;
	(*exp_tok)->is_pipe = false;
	return (EXIT_SUCCESS);
}

/*
	function calculates the size of an array of t_par_tok tokens

	*It declares a variable size of type size_t and initializes it to 0.
	This variable will keep track of the size of the array.

	*It enters a loop that iterates through the par_toks array until
	it encounters a NULL element, indicating the end of the array.

	*Inside the loop, it increments the size variable by 1 for
	each element encountered, effectively counting the number of tokens in the array.

	*Once the loop finishes, it returns the final value of size,
	representing the size of the array.
*/

size_t get_tok_size(t_par_tok *par_toks[])
{
	size_t size;

	size = 0;
	while (par_toks[size])
		size++;
	return (size);
}

/*
	The function is responsible for freeing the memory allocated
	for an array of t_exp_tok tokens and performing some cleanup.

	*It takes as input the array of exp_toks tokens and an exit_status integer.

	*It declares a variable i and initializes it to 0. This variable will be used
	as an index to iterate through the array.

	*It enters a loop that iterates through the exp_toks array until it encounters
	a NULL element, indicating the end of the array.

	*Inside the loop, it performs the following operations:
		-Calls ft_free_str_array to free the memory allocated for the cmd field
		of the current exp_toks token.

		-Calls free to release the memory allocated for the
		current exp_toks token itself.

		-Increments the i variable to move to the next element in the array.

	*After the loop finishes, it frees the memory allocated for
	the exp_toks array itself using free.

	*Calls the reset_exp_toks function to perform any necessary cleanup
	or reset operations related to exp_toks.

	*Finally, it returns the exit_status provided as the function result.
*/

int free_exp_toks(t_exp_tok *exp_toks[], int exit_status)
{
	int i;

	i = 0;
	while (exp_toks[i])
	{
		ft_free_str_array(&exp_toks[i]->cmd);
		free(exp_toks[i]);
		i++;
	}
	free(exp_toks);
	reset_exp_toks();
	return (exit_status);
}

/*
	The  function is responsible for converting an array of t_par_tok tokens
	into an array of t_exp_tok tokens.

	*It takes as input the array of par_toks tokens.

	*It declares a variable exp_toks as a double pointer to t_exp_tok and allocates
	memory for it using ft_calloc. The size of the allocated memory is determined by
	calling get_tok_size on the par_toks array.
	If the memory allocation fails, it returns EXIT_FAILURE.

	*Calls the set_exp_toks function to set the global array exp_toks with
	the allocated memory.

	*Declares a variable i and initializes it to 0. This variable will be used as
	an index to iterate through the par_toks array.

	*Enters a loop that iterates through the par_toks array until it encounters
	a NULL element, indicating the end of the array.

	*Inside the loop, it performs the following operations:

		-Calls the init function to initialize the exp_toks[i] token.
		If the initialization fails (returns EXIT_FAILURE),
		it frees the memory allocated for exp_toks and returns EXIT_FAILURE.

		-Checks if the par_toks[i] token has a non-NULL cmd field.
		If it does, it allocates memory for the exp_toks[i]->cmd field
		using ft_str_arr_dup to duplicate the par_toks[i]->cmd array.
		If the memory allocation fails,
		it frees the memory allocated for exp_toks and returns EXIT_FAILURE.

		-Checks if the par_toks[i] token has the is_in_heredoc flag set in
		its redir_type field. If it does, it calls the wait_for_heredoc
		function to handle the heredoc input for the exp_toks[i] token.
		If wait_for_heredoc returns 1 (indicating an error),
		it frees the memory allocated for exp_toks and returns EXIT_FAILURE.

		-Increments the i variable to move to the next element in the array.
	*After the loop finishes, it returns EXIT_SUCCESS to indicate a
	successful conversion of tokens.
*/

int get_tokens(t_par_tok *par_toks[])
{
	t_exp_tok **exp_toks;
	int i;

	exp_toks = ft_calloc(get_tok_size(par_toks) + 1, sizeof(*exp_toks));
	if (exp_toks == NULL)
		return (EXIT_FAILURE);
	set_exp_toks(exp_toks);
	i = 0;
	while (par_toks[i])
	{
		if (init(&exp_toks[i]) == EXIT_FAILURE)
			return (free_exp_toks(exp_toks, EXIT_FAILURE));
		if (par_toks[i]->cmd)
		{
			exp_toks[i]->cmd = ft_str_arr_dup(par_toks[i]->cmd);
			if (exp_toks[i]->cmd == NULL)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		}
		if (par_toks[i]->redir_type[is_in_heredoc])
			if (wait_for_heredoc(par_toks[i], exp_toks[i], NULL, NULL) == 1)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
	The  function is responsible for reinterpreting environment variables in
	the command array of t_exp_tok tokens.

	*It takes as input the arrays of par_toks and exp_toks tokens.
    
	*Declares two variables i and j and initializes them to 0.
	These variables will be used as indices to iterate through the arrays.
    
	*Enters a loop that iterates through the par_toks and exp_toks arrays as
	long as there are non-NULL tokens and the type field of
	the par_toks[i] token is std.
    
	*Inside the loop, it performs the following operations:
        
		-Sets j to 0 to start iterating through the command
		array of exp_toks[i].
        
		-Enters a nested loop that iterates through the command array
		of exp_toks[i] until it encounters a NULL element,
		indicating the end of the array.
        
		-Inside the nested loop, it performs the following operations:
            
			-Calls the interprete_env_var function to reinterpret
			the environment variable in exp_toks[i]->cmd[j].
			If the reinterpretation fails and returns NULL,
			it returns EXIT_FAILURE to indicate an error.
            
			-Increments j to move to the next element in the command array.
        
		-Increments i to move to the next element in the arrays.
    
	*After the loop finishes, it returns EXIT_SUCCESS
	to indicate a successful reinterpretation of environment variables.
*/

int reinterprete_env_vars(t_par_tok *par_toks[], t_exp_tok *exp_toks[])
{
	int i;
	int j;

	i = 0;
	while (par_toks[i] && exp_toks[i] && par_toks[i]->type == std)
	{
		j = 0;
		while (exp_toks[i]->cmd[j])
		{
			exp_toks[i]->cmd[j] = interpret_env_var(exp_toks[i]->cmd[j]);
			if (exp_toks[i]->cmd[j] == NULL)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
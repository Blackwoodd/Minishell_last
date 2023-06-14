/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:05:52 by nassm             #+#    #+#             */
/*   Updated: 2023/05/31 10:36:59 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is a helper function used by get_env_var_valto handle
	specific cases for variable values in the environment variable context.

	* It checks if the length of the current value is zero and
	if the var is equal to "PWD".
	
		- If both conditions are true, it further checks if the
		length of envar->pwd is zero.
    	If true, it assigns *value to a newly allocated memory block of size 1
		(representing an empty string).
    	If false, it assigns *value to a duplicated string of envar->pwd.
	
	* It checks if the length of the current value is zero and
	if the var is equal to "OLDPWD".
	
		- If both conditions are true, it further checks
		if the length of envar->oldpwd is zero.
		If true, it assigns *value to a newly allocated memory block
		of size 1 (representing an empty string).
    	If false, it assigns *value to a duplicated
		string of envar->oldpwd.

	*It checks if the current envar->env_var[i] is NULL
	and if *value is NULL.

    	- If both conditions are true, it assigns *value to a newly
		allocated memory block of size 1 (representing an empty string).
		
	* Overall, the get_env_var_valnorm function handles special cases
	for variables "PWD" and "OLDPWD" by assigning appropriate values
	to *value based on the contents of envar and the specific conditions.
*/

/*

*/

void	get_env_var_valnorm(t_env *envar, char *var, char **value, int i)
{
	if (ft_strlen(*value) == 0 && ft_strcmp(var, "PWD") == 0)
	{
		if (ft_strlen(envar->pwd) == 0)
			*value = ft_calloc(1, sizeof(char));
		else
			*value = ft_strdup(envar->pwd);
	}
	else if (ft_strlen(*value) == 0 && ft_strcmp(var, "OLDPWD") == 0)
	{
		if (ft_strlen(envar->oldpwd) == 0)
			*value = ft_calloc(1, sizeof(char));
		else
			*value = ft_strdup(envar->oldpwd);
	}
	else if (envar->env_var[i] == NULL && *value == NULL)
		*value = ft_calloc(1, sizeof(char));
}

/*
	The function is responsible for retrieving the value of
	a specific environment variable within the given environment
	variable context envar.

	* It enters a loop to iterate over the environment variables
	stored in envar->env_var.
	{
		* For each iteration, it compares the current variable
		name with the target variable var.
		
		* If the variable names match the condition, it assigns value to
		the substring of envar->env_var[i]
		starting after the '=' character.

    		-If the length of value is zero, it assigns value to a newly
			allocated memory block of size 1 (representing an empty string).
    		- Otherwise, it duplicates the substring and assigns it to value.
    		- The loop is then terminated by the break statement.
	}

	* After the loop, it calls the helper function get_env_var_valnorm
	to handle specific cases and update value accordingly based on the
	contents of envar and the specific condition
	
	* Finally, it returns the resulting value of the environment variable.
*/

char    *get_env_var_val(t_env *envar, char *var)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (envar && envar->env_var && envar->env_var[i] != NULL)
	{
		if (ft_strcmp(var, envar->env_var[i]) == -61)
		{
			value = ft_strchr(envar->env_var[i++], '=') + 1;
			if (ft_strlen(value) == 0)
				value = ft_calloc(1, sizeof(char));
			else
				value = ft_strdup(value);
			break;
		}
		else if (ft_strcmp(var, envar->env_var[i++]) == 0)
		{
			value = ft_calloc(1, sizeof(char));
			break;
		}
	}
	get_env_var_valnorm(envar, var, &value, i);
	return (value);
}

/*
	The function is responsible for initializing
	the t_env structure with the provided environment variables.
*/

t_env	*init_envar(char **envp)
{
	t_env	*envar;

	envar = ft_calloc(1, sizeof(t_env));
	if (envar != NULL && envp != NULL && *envp != NULL)
	{
		envar->envp = envp;
		envar->env_var = ft_str_arr_dup(envp);
		envar->pwd = get_env_var_val(envar, "PWD");
		envar->oldpwd = get_env_var_val(envar,"OLDPWD");
		if (envar->env_var != NULL && envar->pwd != NULL && envar->oldpwd != NULL)
			return (envar);
	}
	return (NULL);
}

/*
	Free a fiven t_env struc
*/

void	free_envar(t_env *envar)
{
	envar->envp = NULL;
	ft_free_str_array(&envar->env_var);
	ft_free_str(&envar->pwd);
	ft_free_str(&envar->oldpwd);
	free(envar);
}

/*
	The function will reinitiate env_var if all values got unset.
*/

int	init_again_envar(t_env	*envar, char **av)
{
	if (*envar->env_var == NULL)
	{
		envar->env_var = ft_realloc_str_arr(envar->env_var, 2);
		if (envar->env_var == NULL)
			return (EXIT_FAILURE);
		envar->env_var[0] = ft_strdup(av[1]);
		if (envar->env_var[0] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

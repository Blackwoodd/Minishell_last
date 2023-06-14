/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:13:03 by nassm             #+#    #+#             */
/*   Updated: 2023/06/14 16:56:04 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function s responsible for retrieving 
	or setting an error code stored in a static variable static_err_code.
	
	* The function takes an err_code parameter and a set_err parameter 
		indicating whether to set the error code or retrieve it.
	* If set_err is true, the err_code is assigned to the 
		static variable static_err_code. 
		This sets the error code to the provided value.
	* Regardless of whether set_err is true or false, the function returns 
		the value of the static variable static_err_code. 
		This retrieves the current error code value.
*/

int	get_error_code(int err_code, bool set_err)
{
	static int	static_err_code = 0;

	if (set_err)
		static_err_code = err_code;
	return (static_err_code);
}

/*
	The functionis used to set an error code and manage 
	a flag last_cmd_ctrlc related to a special case.
	
	* The function has a static boolean variable last_cmd_ctrlc which keeps 
	track of whether the last command was interrupted by Ctrl+C.

	* If last_cmd_ctrlc is true, indicating that the previous command 
	was interrupted, the function resets last_cmd_ctrlc to false 
	and returns, effectively skipping further processing.

	* If err_code is equal to 130, which typically indicates a command 
	terminated by Ctrl+C, the function sets last_cmd_ctrlc to true.

	*The function then calls another function, get_error_code, 
	to update or set the error code using the provided err_code value.
*/

void	set_err_code(int err_code)
{
	static bool	last_cmd_ctrlc = false;

	if (last_cmd_ctrlc)
	{
		last_cmd_ctrlc = false;
		return ;
	}
	if (err_code == 130)
		last_cmd_ctrlc = true;
	get_error_code(err_code, true);
}

int	get_err_code(void)
{
	return (get_error_code(0, false));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:59:33 by nbechon           #+#    #+#             */
/*   Updated: 2023/07/12 14:52:37 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		set_err_code(130);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static bool	first_ctrl_c = true;

static void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		set_err_code(1);
		rl_on_new_line();
		rl_redisplay();
		if (first_ctrl_c)
		{
			write(1, "^C\n", 3);
			first_ctrl_c = false;
		}
		else
		{
			write(1, "^C\n", 4);
			first_ctrl_c = true;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	cmd_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_cmd_signal);
}

void	global_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_global_signal);
}

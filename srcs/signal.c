/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:59:33 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 16:34:28 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int i)
{
	i = 0;
	printf("\nCombinaison Ctrl+C détectée.");
	printf(" Cette combinaison doit jsute relancer le prompt.\n");
}

void	handle_sigquit(int signum)
{
	signum = 0;
	printf("\nCombinaison Ctrl+\\ détectée. Cette combinaison ne fait rien.\n");
}

void	signal_crtl(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sa_quit.sa_handler = handle_sigquit;
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

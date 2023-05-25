/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:15 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 16:59:35 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char **env)
{
	char				*user_input;
	char				*seconde;
	char				*first;

	(void)argc;
	(void)argv;
	if (isatty(STDIN_FILENO))
	{
		signal_crtl();
		while (1)
		{
			user_input = readline("$ ");
			if (user_input == NULL)
				break ;
			add_history(user_input);
			first = take_firstword(user_input);
			seconde = take_second_word(user_input);
			// printf ("%s, %s", first, seconde);
			// exit (0);
			list_of_command(first, seconde, env);
			free(user_input);
		}
	}
	return (0);
}

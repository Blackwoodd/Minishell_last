/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:15 by nbechon           #+#    #+#             */
/*   Updated: 2023/07/25 15:46:56 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_core(void *to_free, int exit_status)
{
	if (exit_status == EXIT_CTRL_D)
		printf ("exit\n");
	rl_clear_history();
	free(to_free);
	return (exit_status);
}

int	core(void)
{
	char	*buff;
	int		exit_code;

	while (true)
	{
		buff = readline("minishell$ ");
		if (buff == NULL)
			return (exit_core((void *)buff, EXIT_CTRL_D));
		if (ft_strlen(buff) > 0)
			add_history(buff);
		exit_code = lexer(buff);
		if (exit_code == EXIT_FAILURE)
			return (exit_core((void *)buff, EXIT_FAILURE));
		free(buff);
	}
	return (exit_core((void *)buff, EXIT_FAILURE));
}

static int	manage_flags(int ac, char *av[])
{
	int	exit_code;

	if (ac != 3 || ft_strcmp(av[1], "-c") != 0)
	{
		ft_fprintf(STDERR_FILENO, "Usage: ./minishell [Flag] \"[Command]\"\n");
		ft_fprintf(STDERR_FILENO, "\t-c\tExecute Command without promot\n");
		return (EXIT_FAILURE);
	}
	exit_code = lexer(av[2]);
	free_envar(get_envar());
	return (exit_code);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*envar;

	global_signal();
	envar = init_envar(envp);
	if (envar == NULL)
		return (EXIT_FAILURE);
	set_envp(envp);
	set_envar(envar);
	if (ac != 1)
		return (manage_flags(ac, av));
	if (core() == EXIT_FAILURE)
	{
		free_envar(envar);
		return (EXIT_FAILURE);
	}
	free_envar(envar);
	return (EXIT_SUCCESS);
}

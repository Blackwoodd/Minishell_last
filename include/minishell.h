/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:10:07 by nbechon           #+#    #+#             */
/*   Updated: 2023/05/25 16:35:54 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ECHO "echo"
# define ECHO_N "echo -n"
# define CD "cd"
# define PWD "pwd"
# define EXIT "exit"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"

///////////////// list_commande.c /////////////////

void	list_of_command(char *first, char *seconde, char **env);

//////////////////// signal.c /////////////////////

void	signal_crtl(void);

//////////////////// commandes.c //////////////////

void	commande_echo(char *first, char *word);
void	commande_pwd(void);
int		commande_cd(char *word);

///////////////// takeword.c ////////////////////

char	*take_second_word(char *user_input);
char	*take_firstword(char *user_input);

//////////////// compare.c //////////////////////

int		compare(char *word, char *tmp);

//////////////// commandes2.c //////////////////

void	commande_env(char **env);
void	commande_export(char **env);
void	commande_unset(char **env, char *var_name);
void	commande_exit(char *seconde);

////////////// all_printf.c ////////////////////

void	printf_exit2(void);
void	printf_exit(char *arg);

///////////////////////////////////////////////////

#endif
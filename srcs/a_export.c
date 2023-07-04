/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:34:20 by nbechon           #+#    #+#             */
/*   Updated: 2023/06/19 15:34:31 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int     commande_export(char **tab)
{
	int             count;
        int             i;
        t_env   	*envar;

        i = 0;
        count = 0;
        envar = get_envar();
        if (envar == NULL || envar->env_var == NULL)
                return (EXIT_FAILURE);
        if (tab[1] != NULL)
        {
                if (tab[1][0] == '-')
                {
                        printf("export: -%c: invalid option\n", tab[1][1]);
                        return (EXIT_FAILURE);
                }
                while (tab[1][i])
                {
                        if (tab[1][i] == '=')
                        count++;
                        if (tab[1][i] == '!')
                        {
                                while (tab[1][i])
                                {
                                        printf ("%c", tab[1][i]);
                                        i++;
                                }
                                printf (": event not found\n");
                                return (EXIT_FAILURE);
                        }
                        i++;
                }
        }
        if (tab[1] && count < 1)
        {
                printf ("export: %s: not a valid identifier\n", tab[2]);
                return (EXIT_FAILURE);
        }
        i = 0;
        if (tab[1] != NULL)
        {
                if (tab[1][0] == '=' || (tab[1][0] >= '0' && tab[1][0] <= '9'))
                {
                          printf ("export: `%s': not a valid identifier\n", tab[1]);
                          return (EXIT_FAILURE);
                }
                while (tab[1][i] != '=')
                {
                        if ((tab[1][i] >= 'A' && tab[1][i] <= 'Z') || (tab[1][i] >= 'a' && tab[1][i] <= 'z')  || (tab[1][i] >= '0' && tab[1][i] <= '9'))
                                i++;
                        else
                        {
                                printf ("export: `%s': not a valid identifier\n", tab[1]);
                                return (EXIT_FAILURE);
                        }
                }
        }
        i = 0;
        if (tab[1] == NULL)
        {
                while (envar->env_var && envar->env_var[i] != NULL)
                {
                        if (ft_printf("export %s\n", envar->env_var[i++]) == 0)
                                return (EXIT_FAILURE);
                }
        }
        else
        {
                int num_env_vars = 0;
                while (envar->env_var[num_env_vars] != NULL)
                        num_env_vars++;
                char *new_env_var = malloc(strlen(tab[1]) + 1);
                if (new_env_var == NULL)
                {
                        printf("Erreur lors de l'allocation de mémoire.\n");
                        return (EXIT_FAILURE);
                }
                strcpy(new_env_var, tab[1]);
                char **new_env_var_list = realloc(envar->env_var, (num_env_vars + 2) * sizeof(char *));
                if (new_env_var_list == NULL)
                {
                        printf("Erreur lors de l'allocation de mémoire.\n");
                        free(new_env_var);
                        return (EXIT_FAILURE);
                }
                new_env_var_list[num_env_vars] = new_env_var;
                new_env_var_list[num_env_vars + 1] = NULL;
                envar->env_var = new_env_var_list;
        }
        return (EXIT_SUCCESS);
}

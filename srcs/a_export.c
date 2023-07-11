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

int     verif_option(char **tab)
{
        if (tab[1] != NULL)
        {
                if (tab[1][0] == '-')
                {
                        printf("export: -%c: invalid option\n", tab[1][1]);
                        return (1);
                }
        }
        return (0);
}

int     verif_event(char **tab, int count)
{
        int     i;
        int     j;

        j = 1;
        while (j <= count)
        {
                i = 0;
                while (tab[j][i])
                {
                        if (tab[j][i] == '!')
                        {
                                while (tab[j][i])
                                {
                                        printf ("%c", tab[j][i]);
                                        i++;
                                }
                                printf (": event not found\n");
                                return (1);
                        }
                        i++;
                }
                j++;
        }
        return (0);
}

int     verif_export_valid(char **tab, int count)
{
        int     i;
        int     j;

        j = 1;
        while (j <= count)
        {
                i = 0;
                if (tab[j] == NULL)
                        j++;
                else if (tab[j][0] == '=' || (tab[j][0] >= '0' && tab[j][0] <= '9'))
                {
                          printf ("export: `%s': not a valid identifier\n", tab[j]);
                          return (1);
                }
                while (tab[j][i] != '=')
                {
                        if (tab[j][i] == '\0')
                                break ;
                        else if ((tab[j][i] >= 'A' && tab[j][i] <= 'Z') || (tab[j][i] >= 'a' && tab[j][i] <= 'z')  || (tab[j][i] >= '0' && tab[j][i] <= '9'))
                                i++;
                        else
                        {
                                printf ("export: `%s': not a valid identifier\n", tab[j]);
                                return (1);
                        }
                }
                j++;
        }
        return (0);
}

int     commande_export(char **tab)
{       
        int             count;
        int             i;
        int             j;
        t_env           *envar;
        
        count = 0;
        j = 1;
        i = 0;
        while (tab[j])
                j++;
        j--;
        envar = get_envar();
        if (tab[1] != NULL && (tab[1][0] < '!' || tab[1][0] > '}'))
                tab[1] = NULL;
        if (envar == NULL || envar->env_var == NULL)
                return (EXIT_FAILURE);
        if (verif_option(tab) == 1)
                return (EXIT_FAILURE);
        if (tab[1] != NULL)
        {
                while (tab[1][i])
                {
                        if (tab[1][i] == '=')
                                count++;
                       i++;
                }
                if (verif_event(tab, j) == 1)
                        return (EXIT_FAILURE);
        }
        if (tab[1] != NULL && tab[2] != NULL && count < 1)
        {
                printf ("export: %s: not a valid identifier\n", tab[2]);
                return (EXIT_FAILURE);
        }
        if (verif_export_valid(tab, j) == 1)
                return (EXIT_FAILURE);
        if (j == 0)
        {
                while (envar->env_var && envar->env_var[i] != NULL)
                {
                        if (ft_printf("export %s\n", envar->env_var[i++]) == 0)
                                return (EXIT_FAILURE);
                }
        }
        i = 1;
        while (i <= j)
        {
                if (tab[i] == NULL)
                printf("export: `': not a valid identifier\n");
                else
                {
                        int num_env_vars = 0;
			int env_var_index = -1;
                        while (envar->env_var[num_env_vars] != NULL)
                        {
                                char* equal_sign = strchr(envar->env_var[num_env_vars], '=');
                                if (equal_sign != NULL && strncmp(envar->env_var[num_env_vars], tab[i], equal_sign - envar->env_var[num_env_vars]) == 0)
                                {
                                        env_var_index = num_env_vars;
                                        break;
                                }
                                num_env_vars++;
                        }
                        char *new_env_var = malloc(strlen(tab[i]) + 1);
                        if (new_env_var == NULL)
                        {
                                printf("Erreur lors de l'allocation de mémoire.\n");
                                return (EXIT_FAILURE);
                        }
                        strcpy(new_env_var, tab[i]);
                        char **new_env_var_list;
                        if (env_var_index != -1)
                        {
                                free(envar->env_var[env_var_index]);
                                new_env_var_list = envar->env_var;
                                new_env_var_list[env_var_index] = new_env_var;
                        }
                        else
                        {
                                new_env_var_list = realloc(envar->env_var, (num_env_vars + 2) * sizeof(char *));
                                if (new_env_var_list == NULL)
                                {
                                        printf ("Erreur lors de l'allocation de memoire.\n");
                                        free (new_env_var);
                                        return (EXIT_FAILURE);
                                }
                                new_env_var_list[num_env_vars] = new_env_var;
                                new_env_var_list[num_env_vars + 1] = NULL;
                        }
                        envar->env_var = new_env_var_list;
                }
                i++;
        }
        return (EXIT_SUCCESS);
}

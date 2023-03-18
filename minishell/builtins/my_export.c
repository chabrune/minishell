/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:24 by emuller           #+#    #+#             */
/*   Updated: 2023/03/18 20:40:45 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

void    add_line_env(t_tools tools, char **var_name, char **var_content)
{
    int count = 0;
    int i = -1;

    (void)tools;
    while (var_name[++i])
        if (var_content[i])
            count++;
    // on dup l'ancien en lui ajoutant le bon nombre de ligne + leur content
    // on free l'ancien env
    return;
}

// fonction export qui recuppere l'env et le trie dans l'orde ascii en ajoutant les variables même vides ++ exrire les contents entre guillemets

// Il faut check si la variable existe deja (strcmp)

// gerer les guillemets

void    my_export(t_tools *tools, t_simple_cmds *cmd)
{
    int i = 0;
    int j = 0;
    int nb_var = 0;
    char **var_name;
    char **var_content;

    while (cmd->str[i])
        i++;
    nb_var = i - 1;
    var_name = ft_calloc(nb_var + 1, sizeof(char*));
    var_content = ft_calloc(nb_var + 1, sizeof(char*));
    i = 0;
    while (i < nb_var)
    {
        j = 0;
        while (cmd->str[i + 1][j] && cmd->str[i + 1][j] != '=')
            j++;
        if (cmd->str[i + 1][j] == '=')
            j++;
        var_name[i] = ft_calloc(j + 2, sizeof(char));
        ft_strlcpy(var_name[i], cmd->str[i + 1], j + 1);
        var_content[i] = ft_strdup(cmd->str[i + 1] + j);
        // printf("VAR = %s\n", var_name[i]);
        // printf("CONTENT = %s\n", var_content[i]);
        i++;
    }
    // add_lines_to_env(tools, var_name, var_content);
    free_tab(var_content, i);
    free_tab(var_name, i);
    return ;
}
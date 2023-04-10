/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:53:08 by emuller           #+#    #+#             */
/*   Updated: 2023/04/10 14:43:07 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int     count_var_to_remove(t_tools *tools, t_simple_cmds *cmd)
{
    int i;
    int j;
    int count;

    count = 0;
    i = -1;
    while (tools->envp[++i])
    {
        j = 0;
        while (cmd->str[++j])
            if (ft_strncmp(tools->envp[i], cmd->str[j], ft_strlen(cmd->str[j])) == 0
                && tools->envp[i][ft_strlen(cmd->str[j])] == '=')
                count++;
    }
    return (count);
}

void    remove_a_var_from_env(t_tools *tools, char *str)
{
    int i;
    int k;
    char **new_tab;

    i = 0;
    k = 0;
    while (tools->envp[i])
        i++;
    new_tab = ft_calloc(i, sizeof(char *));
    if (!new_tab)
        return ;  
    i = 0;
    while (tools->envp[i])
    {
        if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0
            && tools->envp[i][ft_strlen(str)] == '=')
            i++;
        else
            new_tab[k++] = ft_strdup(tools->envp[i++]);
    }
    free_old_env(tools->envp);
    tools->envp = new_tab;
}

int     is_removable(t_tools *tools, char *str)
{
    int i;

    i = -1;
    while (tools->envp[++i])
    {
        if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0
            && tools->envp[i][ft_strlen(str)] == '=')
            return (1);
    }
    return (0);
}

void    my_unset(t_tools *tools, t_simple_cmds *cmd)
{
    int i;
    
    i = 0;
    if (!cmd->str[1])
		return;
    while (cmd->str[++i])
    {
        if (is_removable(tools, cmd->str[i]) == 1)
            remove_a_var_from_env(tools, cmd->str[i]);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:53:08 by emuller           #+#    #+#             */
/*   Updated: 2023/04/09 15:41:40 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    my_unset(t_tools *tools, t_simple_cmds *cmd)
{
    int i=0;
    int j=0;
    int k=0;
    int nb_var = 0;
    char **new_tab;
    
    if (!cmd->str[1])
		return;
    while (cmd->str[i])
        i++;
    nb_var = i - 1;
    i = 0;
    while (tools->envp[i])
        i++;
    new_tab = ft_calloc(i + 1 - nb_var, sizeof(char *));
    if (!new_tab)
        return ;  
    i = 0;
    while (tools->envp[i])
    {
        j = 0;
        while (cmd->str[++j])
        {
            if (ft_strncmp(tools->envp[i], cmd->str[j], ft_strlen(cmd->str[j])) == 0
                && tools->envp[i][ft_strlen(cmd->str[j]) + 1] == '=')
                i++;
            else
		        new_tab[k++] = ft_strdup(tools->envp[i++]);
        }
    }
    free_old_env(tools->envp);
    tools->envp = new_tab;
}
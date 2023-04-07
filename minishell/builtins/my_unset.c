/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:53:08 by emuller           #+#    #+#             */
/*   Updated: 2023/04/07 19:52:20 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    my_unset(t_tools *tools, t_simple_cmds *cmd)
{
    int i=0;
    int j=0;
    int nb_var = 0;
    char **new_tab;
    
    if (!cmd->str[1])
		return;
    while (cmd->str[i])
        i++;
    nb_var = i - 1;
    new_tab = ft_calloc(nb_var + 1, sizeof(char *));
    if (!new_tab)
        return ;  
    i = -1;
    while (tools->envp[++i])
    {
        j = 0;
        while (cmd->str[++j])
        {
            if (ft_strncmp(tools->envp[i], cmd->str[j], ft_strlen(cmd->str[j])) 
                && tools->envp[i][ft_strlen(cmd->str[j]) + 1] == '=')
		        new_tab[i] = ft_strdup(tools->envp[i]);
        }
    }
        // dup env except the lines from cmd->str[i]
        // if it doesn't exist do nothing
}
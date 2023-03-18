/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:34:18 by emuller           #+#    #+#             */
/*   Updated: 2023/03/18 18:55:31 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_exit(t_tools *tools, t_simple_cmds *cmds)
{
	//free_all();
	(void)tools;
	(void)cmds;
	exit(0);
}

void	choose_bultins(t_tools *tools, t_simple_cmds *cmds)
 {
	t_simple_cmds *tmp;
	tmp = cmds;
	while (tmp)
	{
		if (ft_strncmp("pwd", cmds->str[0], 3) == 0)
			my_pwd(tools);
		else if (ft_strncmp("echo", cmds->str[0], 4) == 0)
			my_echo(cmds);
		else if (ft_strncmp("cd", cmds->str[0], 2) == 0)
			my_cd(tools, cmds);
		else if (ft_strncmp("export", cmds->str[0], 6) == 0)
			my_export(tools, cmds) ;
		else if (ft_strncmp("unset", cmds->str[0], 5) == 0)
			return ;
		else if (ft_strncmp("env", cmds->str[0], 3) == 0)
			my_env(tools, cmds);
		else if (ft_strncmp("exit", cmds->str[0], 4) == 0)
			my_exit(tools, cmds);
		tmp = tmp->next;
	}
 }
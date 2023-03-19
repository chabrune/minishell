/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:50:59 by emuller           #+#    #+#             */
/*   Updated: 2023/03/19 17:45:45 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_pwd(t_tools *tools)
{
	int	i;
	char *pwd;

	i = -1;
	while (tools->envp[++i])
		if(ft_strncmp(tools->envp[i], "PWD=", 4) == 0)
			pwd = ft_strdup(tools->envp[i]);
	ft_putendl_fd(pwd + 4, 1);
	free(pwd);
}

void	my_env(t_tools *tools, t_simple_cmds *cmd)
{
	int	i;

	i = -1;
	if (cmd->str[1])
	{
		ft_putendl_fd("env does not handle args", 2);
		return ;
	}
	while (tools->envp[++i])
		if (ft_strchr(tools->envp[i], '=') != 0)
			ft_putendl_fd(tools->envp[i], 1);
}
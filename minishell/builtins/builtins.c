/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:34:18 by emuller           #+#    #+#             */
/*   Updated: 2023/03/12 15:37:49 by chabrune         ###   ########.fr       */
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

void	my_echo(t_simple_cmds *cmd)
{
	int		i;
	bool	n;

	i = 1;
	n = 0;
	while (cmd->str[1] && cmd->str[1][0] == '-' && cmd->str[1][i] == 'n')
	{
		i++;
		if (cmd->str[1][i] == 0)
			n = 1;	
	}
	if (i > 1)
		i = 2;
	while (cmd->str[i])
	{
		ft_putstr_fd(cmd->str[i], 1);
		i++; 
		if (cmd->str[i])
			ft_putchar_fd(' ', 1);
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
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
		ft_putendl_fd(tools->envp[i], 1);
}

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
			return;
			// my_cd(tools, cmds);
		else if (ft_strncmp("export", cmds->str[0], 6) == 0)
			return ;
		else if (ft_strncmp("unset", cmds->str[0], 5) == 0)
			return ;
		else if (ft_strncmp("env", cmds->str[0], 3) == 0)
			my_env(tools, cmds);
		else if (ft_strncmp("exit", cmds->str[0], 4) == 0)
			my_exit(tools, cmds);
		tmp = tmp->next;
	}
 }
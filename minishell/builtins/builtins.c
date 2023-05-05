/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:34:18 by emuller           #+#    #+#             */
/*   Updated: 2023/05/08 18:31:42 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	my_exit(t_tools *tools, t_simple_cmds *cmds, t_lexer *lexer)
{
	if (lexer)
		lstclear_lexer(&lexer, free);
	if (cmds)
		lstclear_cmds(&cmds, free);
	if (tools)
		lstclear_tools(tools);
	exit(0);
}

void	my_exit_2(t_tools *tools, t_simple_cmds *cmds)
{
	if (cmds->str[1] && ft_atoi(cmds->str[1]) != 0)
		g_global.error_num = ft_atoi(cmds->str[1]);
	else if (cmds->str[1])
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
	if (cmds)
		lstclear_cmds(&cmds, free);
	if (tools)
		lstclear_tools(tools);
	exit(g_global.error_num);
}

int	builtins_to_fork(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;

	tmp = cmds;
	if (!cmds->str)
		return (1);
	while (tmp)
	{
		if (ft_strncmp("pwd", cmds->str[0], 3) == 0)
			return (1);
		else if (ft_strncmp("echo", cmds->str[0], 4) == 0)
			return (1);
		else if (ft_strncmp("env", cmds->str[0], 3) == 0)
			return (1);
		else if (ft_strncmp("export", cmds->str[0], 6) == 0 && !cmds->str[1])
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_builtins(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;

	tmp = cmds;
	if (!cmds->str)
		return (1);
	while (tmp)
	{
		if (ft_strncmp("pwd", cmds->str[0], 3) == 0)
			return (1);
		else if (ft_strncmp("echo", cmds->str[0], 4) == 0)
			return (1);
		else if (ft_strncmp("cd", cmds->str[0], 2) == 0)
			return (1);
		else if (ft_strncmp("export", cmds->str[0], 6) == 0 && cmds->str[1])
			return (1);
		else if (ft_strncmp("unset", cmds->str[0], 5) == 0)
			return (1);
		else if (ft_strncmp("env", cmds->str[0], 3) == 0)
			return (1);
		else if (ft_strncmp("exit", cmds->str[0], 4) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	choose_bultins_multiple(t_tools *tools, t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;

	tmp = cmds;
	if (!cmds->str)
		return ;
	while (tmp)
	{
		if (ft_strncmp("pwd", cmds->str[0], 3) == 0)
			my_pwd(tools);
		else if (ft_strncmp("echo", cmds->str[0], 4) == 0)
			my_echo(cmds);
		else if (ft_strncmp("cd", cmds->str[0], 2) == 0)
			my_cd(tools, cmds);
		else if (ft_strncmp("export", cmds->str[0], 6) == 0)
			my_export(tools, cmds);
		else if (ft_strncmp("unset", cmds->str[0], 5) == 0)
			my_unset(tools, cmds);
		else if (ft_strncmp("env", cmds->str[0], 3) == 0)
			my_env(tools, cmds);
		else if (ft_strncmp("exit", cmds->str[0], 4) == 0)
			my_exit_2(tools, cmds);
		tmp = tmp->next;
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:22:03 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/13 14:42:11 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	choose_bultins_one(t_tools *tools, t_simple_cmds *cmds, t_lexer *lexer)
{
	t_simple_cmds	*tmp;

	tmp = cmds;
	if (!cmds->str)
		return ;
	while (tmp)
	{
		choose_builtins_one_split(cmds, tools);
		choose_builtins_one_split_two(cmds, tools, lexer);
		tmp = tmp->next;
	}
}

void	choose_builtins_one_split(t_simple_cmds *cmds, t_tools *tools)
{
	if (ft_strncmp("pwd", cmds->str[0], 3) == 0)
	{
		my_pwd(tools);
		exit(0);
	}
	else if (ft_strncmp("echo", cmds->str[0], 4) == 0)
	{
		my_echo(cmds);
		exit(0);
	}
	else if (ft_strncmp("env", cmds->str[0], 3) == 0)
	{
		my_env(tools, cmds);
		exit(0);
	}
}

void	choose_builtins_one_split_two(t_simple_cmds *cmds, t_tools *tools,
		t_lexer *lexer)
{
	(void)lexer;
	if (ft_strncmp("exit", cmds->str[0], 4) == 0)
	{
		write(2, "exit\n", 5);
		my_exit_2(tools, cmds);
	}
	else if (ft_strncmp("export", cmds->str[0], 6) == 0 && !cmds->str[1])
	{
		my_export(tools, cmds, -1, 0);
		exit(0);
	}
	else if (ft_strncmp("cd", cmds->str[0], 2) == 0)
		my_cd(tools, cmds);
	else if (ft_strncmp("export", cmds->str[0], 6) == 0 && cmds->str[1])
		my_export(tools, cmds, -1, 0);
	else if (ft_strncmp("unset", cmds->str[0], 5) == 0)
		my_unset(tools, cmds);
}

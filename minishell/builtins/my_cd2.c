/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:29:26 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/14 15:58:46 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	change_dir(t_tools *tools, char *path, char *old_pwd)
{
	int	check_err;

	check_err = chdir(path);
	if (check_err >= 0)
		change_env(tools, path, old_pwd);
	return (check_err);
}

void	my_cd(t_tools *tools, t_simple_cmds *cmds)
{
	char	*home;
	char	*pwd;
	char	*old_pwd;
	int		check_err;

	home = NULL;
	pwd = NULL;
	find_pwd(tools, &home, &pwd);
	if (!home)
	{
		if (pwd)
			free(pwd);
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_global.error_num = 1;
		return ;
	}
	old_pwd = ft_strdup(pwd);
	if (!(cmds->str[1]))
		check_err = change_dir(tools, home, old_pwd);
	else if (cmds->str[1][0] == '/')
		check_err = change_dir(tools, cmds->str[1], old_pwd);
	else
	{
		home = find_relative_path(cmds, &pwd, home);
		check_err = change_dir(tools, home, old_pwd);
	}
	if (check_err == -1)
	{
		g_global.error_num = 1;
		ft_putendl_fd("minishell: No such file or directory", 2);
	}
	free(old_pwd);
	if (pwd)
		free(pwd);
	if (home)
		free(home);
}

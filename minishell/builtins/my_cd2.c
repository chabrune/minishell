/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:29:26 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/14 16:53:43 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	change_dir(t_tools *tools, char *path, char *old_pwd)
{
	int	check_err;

	if (path)
		check_err = chdir(path);
	else
		check_err = -1;
	if (check_err >= 0)
		change_env(tools, path, old_pwd);
	return (check_err);
}

void	cd_error(char *home)
{
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_global.error_num = 1;
	}
	else
		ft_putendl_fd("minishell: No such file or directory", 2);
	g_global.error_num = 1;
}

void	free_cd(char *old_pwd, char *pwd, char *home)
{
	free(old_pwd);
	if (pwd)
		free(pwd);
	if (home)
		free(home);
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
		cd_error(home);
	free_cd(old_pwd, pwd, home);
}

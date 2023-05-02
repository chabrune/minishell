/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:19:46 by emuller           #+#    #+#             */
/*   Updated: 2023/05/02 16:35:43 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*find_parent_dir(char *pwd)
{
	char	*str;
	int		i;

	i = 0;
	while (pwd[i])
		i++;
	i--;
	while (pwd[i] && pwd[i] != '/')
		i--;
	str = ft_calloc(i + 2, sizeof(char));
	ft_strlcpy(str, pwd, i + 1);
	return (str);
}

void	change_env(t_tools *tools, char *path, char *old_pwd)
{
	int	i;

	i = -1;
	while (tools->envp[++i])
	{
		if (ft_strncmp(tools->envp[i], "PWD=", 4) == 0)
		{
			free(tools->envp[i]);
			tools->envp[i] = ft_strjoin("PWD=", path);
		}
		else if (ft_strncmp(tools->envp[i], "OLDPWD=", 7) == 0)
		{
			free(tools->envp[i]);
			tools->envp[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
	}
}

char	*find_relative_path(t_simple_cmds *cmds, char **pwd, char *home)
{
	int		i;
	char	*path;

	i = 0;
	while (cmds->str[1][i] == '.' && cmds->str[1][i + 1] == '.')
	{
		*pwd = find_parent_dir(*pwd);
		i += 2;
		if (cmds->str[1][i] == '/')
			i++;
	}
	if (cmds->str[1][i] == '.')
		i++;
	if (i == 0 && cmds->str[1][i] == '~')
	{
		*pwd = ft_strdup(home);
		i++;
	}
	if (i == 0)
		*pwd = ft_strjoin(*pwd, "/");
	path = ft_strjoin(*pwd, cmds->str[1] + i);
	return (path);
}

char	*find_path_ret(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		if (!ft_strncmp(tools->envp[i], "OLDPWD=", 7))
			return (ft_substr(tools->envp[i], 7,
					ft_strlen(tools->envp[i]) - 7));
		i++;
	}
	return (0);
}

int	change_old_pwd(t_tools *tools)
{
	char	*tmp;
	int		ret;
	char	*str;

	tmp = find_path_ret(tools);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr("OLDPWD=", 0, 6);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	my_cd(t_tools *tools, t_simple_cmds *cmds)
{
	char	*home;
	char	*pwd;
	char	*old_pwd;
	int		i;
	int		check_err;

	i = -1;
	check_err = 0;
	while (tools->envp[++i])
	{
		if (ft_strncmp(tools->envp[i], "HOME=", 5) == 0)
			home = tools->envp[i] + 5;
		else if (ft_strncmp(tools->envp[i], "PWD=", 4) == 0)
			pwd = tools->envp[i] + 4;
	}
	old_pwd = ft_strdup(pwd);
	if (!(cmds->str[1]))
	{
		check_err = chdir(home);
		if (check_err >= 0)
			change_env(tools, home, old_pwd);
	}
	// else if (ft_strncmp(cmds->str[1], "-", 1) == 0)
	// {
	// 	change_old_pwd(tools);
	// }
	else if (cmds->str[1][0] == '/')
	{
		check_err = chdir(cmds->str[1]);
		if (check_err >= 0)
			change_env(tools, cmds->str[1], old_pwd);
	}
	else
	{
		home = find_relative_path(cmds, &pwd, home);
		check_err = chdir(home);
		if (check_err >= 0)
			change_env(tools, home, old_pwd);
	}
	if (check_err == -1)
	{
		ft_putendl_fd("No such file or directory", 2);
	}
	free(old_pwd);
}

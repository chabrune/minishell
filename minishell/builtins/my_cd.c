/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:19:46 by emuller           #+#    #+#             */
/*   Updated: 2023/05/12 15:40:51 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*find_parent_dir(char **pwd)
{
	char	*str;
	int		i;

	i = 0;
	while ((*pwd)[i])
		i++;
	i--;
	while ((*pwd)[i] && (*pwd)[i] != '/')
		i--;
	str = ft_calloc(i + 2, sizeof(char));
	ft_strlcpy(str, *pwd, i + 1);
	free(*pwd);
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

char	*ft_strjoin_without_leaks(char *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	free(s1);
	return (str);
}

char	*find_relative_path(t_simple_cmds *cmds, char **pwd, char *home)
{
	int		i;
	char	*path;

	i = 0;
	while (cmds->str[1][i] == '.' && cmds->str[1][i + 1] == '.')
	{
		*pwd = find_parent_dir(&(*pwd));
		i += 2;
		if (cmds->str[1][i] == '/')
			i++;
	}
	if (cmds->str[1][i] == '.')
		i++;
	if (i == 0 && cmds->str[1][i] == '~')
	{
		free(*pwd);
		*pwd = ft_strdup(home);
		i++;
	}
	if (i == 0)
		*pwd = ft_strjoin_without_leaks(*pwd, "/");
	path = ft_strjoin(*pwd, cmds->str[1] + i);
	free(home);
	return (path);
}

void	find_pwd(t_tools *tools, char **home, char **pwd)
{
	int	i;

	i = -1;
	while (tools->envp[++i])
	{
		if (ft_strncmp(tools->envp[i], "HOME=", 5) == 0)
			*home = ft_strdup(tools->envp[i] + 5);
		else if (ft_strncmp(tools->envp[i], "PWD=", 4) == 0)
			*pwd = ft_strdup(tools->envp[i] + 4);
	}
}

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
	{
		g_global.error_num = 1;
		ft_putendl_fd("bash: No such file or directory", 2);
	}
	free(old_pwd);
	free(pwd);
	free(home);
}

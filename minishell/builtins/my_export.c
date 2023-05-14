/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:24 by emuller           #+#    #+#             */
/*   Updated: 2023/05/14 16:28:08 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	*free_old_env(char **tab)
{
	int	k;

	k = 0;
	while (tab[k])
	{
		free(tab[k]);
		k++;
	}
	free(tab);
	return (0);
}

int	var_name_is_new(t_tools *tools, char *var)
{
	int		j;
	char	*tmp_env;
	int		i;

	i = -1;
	while (tools->envp[++i])
	{
		j = 0;
		while (tools->envp[i][j] && tools->envp[i][j] != '=')
			j++;
		if (tools->envp[i][j] == '=')
			j++;
		tmp_env = ft_calloc(j + 2, sizeof(char));
		ft_strlcpy(tmp_env, tools->envp[i], j + 1);
		if (ft_strncmp(var, tmp_env, ft_strlen(var)) == 0)
		{
			free(tmp_env);
			if (ft_strlen(var) > 0)
				if (var[ft_strlen(var) - 1] != '=')
					return (2);
			return (1);
		}
		free(tmp_env);
	}
	return (0);
}

char	**fill_env(char **tab, int nb_new_lines, char **var_name,
		char **var_content)
{
	char	**new_tab;
	int		i;
	int		j;
	int		len_new_tab;

	i = 0;
	while (tab[i])
		i++;
	len_new_tab = i + nb_new_lines;
	new_tab = ft_calloc(sizeof(char *), len_new_tab + 1);
	if (!new_tab)
		return (0);
	i = -1;
	while (tab[++i] && tab[i + 1])
		new_tab[i] = ft_strdup(tab[i]);
	j = 0;
	while (i < len_new_tab - 1)
	{
		new_tab[i++] = ft_strjoin(var_name[j], var_content[j]);
		j++;
	}
	new_tab[i] = ft_strdup(tab[i - nb_new_lines]);
	free_old_env(tab);
	return (new_tab);
}

void	add_lines_to_env(t_tools *tools, char **var_name, char **var_content)
{
	int	count_newlines;
	int	i;
	int	j;

	j = 0;
	count_newlines = 0;
	i = -1;
	while (var_name[++i])
		count_newlines++;
	tools->envp = fill_env(tools->envp, count_newlines - j, var_name,
			var_content);
}

void	pour_la_norme(char ***sorted_env)
{
	int	i;
	int	j;

	i = -1;
	while ((*sorted_env)[++i])
	{
		j = 0;
		write(1, "declare -x ", 11);
		while ((*sorted_env)[i][j] && (*sorted_env)[i][j] != '=')
			write(1, &(*sorted_env)[i][j++], 1);
		if ((*sorted_env)[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while ((*sorted_env)[i][j])
				write(1, &(*sorted_env)[i][j++], 1);
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
	}
}

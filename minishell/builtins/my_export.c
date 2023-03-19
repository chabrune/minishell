/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:24 by emuller           #+#    #+#             */
/*   Updated: 2023/03/19 17:53:54 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

// Il faut check si la variable existe deja (strcmp)
// gerer les guillemets

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

char	**fill_env(char **tab, int nb_new_lines, char **var_name, char **var_content)
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

void    add_lines_to_env(t_tools *tools, char **var_name, char **var_content)
{
    int count_newlines = 0;
    int i = -1;

    while (var_name[++i])
        count_newlines++;
	tools->envp = fill_env(tools->envp, count_newlines, var_name, var_content);
}

void    print_export(t_tools *tools)
{
	char	*tmp;
	int		i;
	char	**sorted_env;

	sorted_env = dup_env(tools->envp);
	tmp = 0;
	i = 0;
	while (sorted_env[i + 1])
	{
		if (ft_strcmp(sorted_env[i], sorted_env[i + 1]) > 0)
		{
			tmp = sorted_env[i];
			sorted_env[i] = sorted_env[i + 1];
			sorted_env[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	i = -1;
	while (sorted_env[++i])
	{
		int	j = 0;
		write(1, "declare -x ", 11);
		while (sorted_env[i][j] && sorted_env[i][j] != '=')
			write(1, &sorted_env[i][j++], 1);
		if (sorted_env[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while (sorted_env[i][j])
				write(1, &sorted_env[i][j++], 1);
			write(1, "\"\n", 2);
		}
		else
			write(1, "\n", 1);
	}
    return ;
}

void    my_export(t_tools *tools, t_simple_cmds *cmd)
{
    int i = 0;
    int j = 0;
    int nb_var = 0;
    char **var_name;
    char **var_content;

    if (!cmd->str[1])
	{
		print_export(tools);
		return;
	}
	while (cmd->str[i])
        i++;
    nb_var = i - 1;
    var_name = ft_calloc(nb_var + 1, sizeof(char*));
    var_content = ft_calloc(nb_var + 1, sizeof(char*));
    i = 0;
    while (i < nb_var)
    {
        j = 0;
        while (cmd->str[i + 1][j] && cmd->str[i + 1][j] != '=')
            j++;
        if (cmd->str[i + 1][j] == '=')
            j++;
        var_name[i] = ft_calloc(j + 2, sizeof(char));
        ft_strlcpy(var_name[i], cmd->str[i + 1], j + 1);
        var_content[i] = ft_strdup(cmd->str[i + 1] + j);
        i++;
    }
    add_lines_to_env(tools, var_name, var_content);
    free_tab(var_content, i);
    free_tab(var_name, i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:24 by emuller           #+#    #+#             */
/*   Updated: 2023/04/20 18:43:05 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// Il faut check si la variable existe deja (strcmp)
// Il faut aussi gerer les += 

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

	count_newlines = 0;
	i = -1;
	while (var_name[++i])
	{
		count_newlines++;
	}
	tools->envp = fill_env(tools->envp, count_newlines, var_name, var_content);
}

void	print_export(t_tools *tools)
{
	char	*tmp;
	int		i;
	char	**sorted_env;
	int		j;

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
		j = 0;
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

void	remove_useless_dquotes(char **var_content, int check_quote, int i)
{
	int j = -1;
	while (var_content[i][++j])
		if (var_content[i][j] == '\"' && check_quote == 1)
		{
			while (var_content[i][j] && var_content[i][j + 1])
			{
				var_content[i][j] = var_content[i][j + 1];
				j++;
			}
			var_content[i][j] = 0;
		}
}

void	remove_useless_squotes(char **var_content, int check_quote, int i)
{
	int j;
	
	j = -1;
	while (var_content[i][++j])
		if (var_content[i][j] == '\'' && check_quote == 2)
		{
			while (var_content[i][j] && var_content[i][j + 1])
			{
				var_content[i][j] = var_content[i][j + 1];
				j++;
			}
			var_content[i][j] = 0;
		}
}

void	fill_var_content(t_simple_cmds *cmd, int i, int j, char **var_content)
{
		int	check_quote = 0;
		if (cmd->str[i + 1][j] == '\"')
		{
			j++;
			check_quote = 1;
		}
		else if (cmd->str[i + 1][j] == '\'')
		{
			j++;
			check_quote = 2;
		}
		if (*var_content)
			free(*var_content);
		*var_content = ft_strdup(cmd->str[i + 1] + j);
		remove_useless_dquotes(var_content, check_quote, i);
		remove_useless_squotes(var_content, check_quote, i);
}

int		fill_var_name(t_simple_cmds *cmd, char **var_name, int i)
{
	int j;

	j = 0;
	while (cmd->str[i + 1][j] && cmd->str[i + 1][j] != '=')
		j++;
	if (cmd->str[i + 1][j] == '=')
		j++;
	*var_name = ft_calloc(j + 2, sizeof(char));
	ft_strlcpy(*var_name, cmd->str[i + 1], j + 1);
	return (j);
}

int		count_var(t_simple_cmds *cmd) // Il faut aussi verfier qur la variable n'existe pas deja 
{
	int i;

	i = 0;
	while (cmd->str[i])
		i++;
	return (i - 1);
}

int		var_name_is_new(t_tools *tools, char	*var)
{
	int j;
	char *tmp_env;
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		j = 0;
		while (tools->envp[i][j] && tools->envp[i][j] != '=')
			j++;
		if (tools->envp[i][j] == '=')
			j++; 
		tmp_env = ft_calloc(j + 2, sizeof(char));
		ft_strlcpy(tmp_env, tools->envp[i], j + 1);
		if (ft_strncmp(var, tmp_env, ft_strlen(var)) == 0 && var[ft_strlen(var)] == '=')
		{
			free(tmp_env);
			return (1);
		}
		free(tmp_env);
		i++;
	}
	return (0);
}

void	my_export(t_tools *tools, t_simple_cmds *cmd)
{
	int		i;
	int		j;
	int		nb_var;
	char	**var_name;
	char	**var_content;

	if (!cmd->str[1])
	{
		print_export(tools);
		return ;
	}
	nb_var = count_var(cmd);
	var_name = ft_calloc(nb_var + 1, sizeof(char *)); 
	var_content = ft_calloc(nb_var + 1, sizeof(char *));
	i = -1;
	while (++i < nb_var)
	{
		j = fill_var_name(cmd, &var_name[i], i);
			fill_var_content(cmd, i, j, &var_content[i]);
	}
		// if (var_name_is_new(tools, var_name[i]) == 0) il faut peut etre creer un tableau avec les index a ne pas changer
	add_lines_to_env(tools, var_name, var_content);
	free_tab(var_content, i);
	free_tab(var_name, i);
}

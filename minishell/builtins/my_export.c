/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:24 by emuller           #+#    #+#             */
/*   Updated: 2023/05/08 15:23:47 by emuller          ###   ########.fr       */
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
		if (ft_strncmp(var, tmp_env, ft_strlen(var)) == 0)
		{
			free(tmp_env);
			if (var[ft_strlen(var) - 1] != '=')
				return (2);
			return (1);
		}
		free(tmp_env);
		i++;
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
	int	j;

	j = -1;
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
	int	j;

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
	int	check_quote;

	check_quote = 0;
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

int	check_valid_name(char *var)
{
	int	i;

	i = 0;
	if (var[i] != '_' && !ft_isalpha(var[i]))
		return (-1);
	i++;
	while (var[i] && (ft_isalpha(var[i]) || var[i] == '_' || ft_isdigit(var[i])))
		i++;
	if (var[i] == '=')
		i++;
	if (var[i])
		return (-1);
	return (0);
}

int	fill_var_name(t_simple_cmds *cmd, char **var_name, int i)
{
	int	j;

	j = 0;
	while (cmd->str[i + 1][j] && cmd->str[i + 1][j] != '=')
		j++;
	if (cmd->str[i + 1][j] == '=')
		j++;
	*var_name = ft_calloc(j + 2, sizeof(char));
	ft_strlcpy(*var_name, cmd->str[i + 1], j + 1);
	if (check_valid_name(*var_name) == -1)
	{
		error_num = 1;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(*var_name, 2);
		ft_putendl_fd(" : not a valid identifier", 2);
		return (-1);
	}
	return (j);
}

int	count_var(t_simple_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->str[i])
		i++;
	return (i - 1);
}

void	remove_a_var_from_env_2(t_tools *tools, char *str)
{
	int		i;
	int		k;
	char	**new_tab;

	i = 0;
	k = 0;
	while (tools->envp[i])
		i++;
	new_tab = ft_calloc(i, sizeof(char *));
	if (!new_tab)
		return ;
	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0)
			i++;
		else
			new_tab[k++] = ft_strdup(tools->envp[i++]);
	}
	free_old_env(tools->envp);
	tools->envp = new_tab;
}

int	is_removable_2(t_tools *tools, char *str)
{
	int	i;

	i = -1;
	while (tools->envp[++i])
	{
		if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}

void	my_unset_2(t_tools *tools, char *var)
{
	if (!var)
		return ;
	if (is_removable_2(tools, var) == 1)
		remove_a_var_from_env_2(tools, var);
}

void	ignore_var(char ***var_name, char ***var_content, int i)
{
	int	j;

	j = 0;
	while ((*var_name)[j])
	{
		if (j == i)
		{
			while ((*var_name)[j])
			{
				free((*var_name)[j]);
				(*var_name)[j] = 0;
				free((*var_content)[j]);
				(*var_content)[j] = 0;
				if ((*var_name)[j + 1])
				{
					(*var_name)[j] = ft_strdup((*var_name)[j + 1]);
					(*var_content)[j] = ft_strdup((*var_content)[j + 1]);
				}
				j++;
			}
		}
		j++;
	}
}

void	my_export(t_tools *tools, t_simple_cmds *cmd)
{
	int		i;
	int		j;
	int		nb_var;
	char	**var_name;
	char	**var_content;
	char	*tmp;

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
		if (j < 0)
			return ;
		tmp = ft_calloc(sizeof(char), ft_strlen(var_name[i]));
		ft_strlcpy(tmp, var_name[i], ft_strlen(var_name[i]));
		if (var_name_is_new(tools, tmp) == 2)
			my_unset_2(tools, tmp);
		if (var_name_is_new(tools, var_name[i]) == 1)
			my_unset_2(tools, var_name[i]);
		fill_var_content(cmd, i, j, &var_content[i]);
		if (var_name_is_new(tools, var_name[i]) == 2)
			ignore_var(&var_name, &var_content, i);
	}
	add_lines_to_env(tools, var_name, var_content);
	free_tab(var_content, i);
	free_tab(var_name, i);
}

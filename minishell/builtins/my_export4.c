/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:30:55 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/12 21:32:55 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_export(t_tools *tools)
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
	pour_la_norme(&sorted_env);
	free_old_env(sorted_env);
	return ;
}

int	count_var(t_simple_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->str[i])
		i++;
	return (i - 1);
}

void	my_export(t_tools *tools, t_simple_cmds *cmd, int i, int j)
{
	int		nb_var;
	char	**var_name;
	char	**var_content;

	if (!cmd->str[1])
		return (print_export(tools));
	nb_var = count_var(cmd);
	var_name = ft_calloc(nb_var + 1, sizeof(char *));
	var_content = ft_calloc(nb_var + 1, sizeof(char *));
	while (++i < nb_var)
	{
		j = fill_var_name(cmd, &var_name[i], i);
		if (j < 0)
			return ;
		check_existing_name(tools, &var_name, &i);
		fill_var_content(cmd, i, j, &var_content[i]);
		if (var_name_is_new(tools, var_name[i]) == 2)
			ignore_var(&var_name, &var_content, i);
	}
	add_lines_to_env(tools, var_name, var_content);
	free_tab(var_content, i);
	free_tab(var_name, i);
}

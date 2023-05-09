/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 00:07:07 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/09 17:38:44 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_useless_dquotes(char **var_content, int check_quote, int i)
{
	int	j;

	j = -1;
	while (var_content[i][++j])
	{
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
}

void	remove_useless_squotes(char **var_content, int check_quote, int i)
{
	int	j;

	j = -1;
	while (var_content[i][++j])
	{
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
	while (var[i] && (ft_isalpha(var[i]) || var[i] == '_'
			|| ft_isdigit(var[i])))
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
		g_global.error_num = 1;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(*var_name, 2);
		ft_putendl_fd(" : not a valid identifier", 2);
		return (-1);
	}
	return (j);
}

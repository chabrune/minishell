/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:53:08 by emuller           #+#    #+#             */
/*   Updated: 2023/05/09 17:40:07 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_a_var_from_env(t_tools *tools, char *str)
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
		if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0
			&& (tools->envp[i][ft_strlen(str)] == '='
				|| tools->envp[i][ft_strlen(str)] == 0))
			i++;
		else
			new_tab[k++] = ft_strdup(tools->envp[i++]);
	}
	free_old_env(tools->envp);
	tools->envp = new_tab;
}

int	is_removable(t_tools *tools, char *str)
{
	int	i;

	i = -1;
	while (tools->envp[++i])
	{
		if (ft_strncmp(tools->envp[i], str, ft_strlen(str)) == 0
			&& (tools->envp[i][ft_strlen(str)] == '='
				|| tools->envp[i][ft_strlen(str)] == 0))
			return (1);
	}
	return (0);
}

int	check_valid_name_unset(char *var)
{
	int	i;

	i = 0;
	if (var[i] != '_' && !ft_isalpha(var[i]))
		return (-1);
	i++;
	while (var[i] && (ft_isalpha(var[i]) || var[i] == '_'
			|| ft_isdigit(var[i])))
		i++;
	if (var[i])
		return (-1);
	return (0);
}

void	my_unset(t_tools *tools, t_simple_cmds *cmd)
{
	int	i;

	i = 0;
	if (!cmd->str[1])
		return ;
	while (cmd->str[++i])
	{
		if (check_valid_name_unset(cmd->str[i]) == -1)
		{
			g_global.error_num = 1;
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd->str[i], 2);
			ft_putendl_fd(" : not a valid identifier", 2);
		}
		if (is_removable(tools, cmd->str[i]) == 1)
			remove_a_var_from_env(tools, cmd->str[i]);
	}
}

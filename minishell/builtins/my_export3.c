/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 00:09:08 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/14 15:59:56 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

void	check_existing_name(t_tools *tools, char ***var_name, int *i)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char), ft_strlen((*var_name)[*i]));
	ft_strlcpy(tmp, (*var_name)[*i], ft_strlen((*var_name)[*i]));
	if (var_name_is_new(tools, tmp) == 2)
		my_unset_2(tools, tmp);
	if (var_name_is_new(tools, (*var_name)[*i]) == 1)
		my_unset_2(tools, (*var_name)[*i]);
	free(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:00:57 by emuller           #+#    #+#             */
/*   Updated: 2023/05/14 16:22:05 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	free_expanded(char **var_name, char **var_content, int j)
{
	while (--j >= 0)
	{
		free(var_name[j]);
		free(var_content[j]);
	}
	free(var_name);
	free(var_content);
}

char	**get_var_name_array(int nb_dollar)
{
	return (ft_calloc(nb_dollar + 1, sizeof(char *)));
}

char	**get_var_content_array(int nb_dollar)
{
	return (ft_calloc(nb_dollar + 1, sizeof(char *)));
}

void	fill_var_arrays(char *str, t_tools *tools, char **var_name,
			char **var_content)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			var_name[j] = ft_strdup("?");
			var_content[j] = ft_itoa(g_global.error_num);
			j++;
		}
		else if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			var_name[j] = find_var_name(str, i);
			var_content[j] = find_var_env(tools, var_name[j]);
			j++;
		}
	}
}

char	*expand_str(int nb_dollar, char *result, char *str, t_tools *tools)
{
	char	**var_name;
	char	**var_content;

	var_name = get_var_name_array(nb_dollar);
	var_content = get_var_content_array(nb_dollar);
	if (!var_name || !var_content)
		return (0);
	fill_var_arrays(str, tools, var_name, var_content);
	result = replace_name_with_content(str, var_name, var_content, nb_dollar);
	free_expanded(var_name, var_content, nb_dollar);
	return (result);
}

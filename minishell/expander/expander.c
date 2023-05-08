/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:00:57 by emuller           #+#    #+#             */
/*   Updated: 2023/05/08 17:28:42 by emuller          ###   ########.fr       */
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

char	*expand_str(int nb_dollar, char *result, char *str, t_tools *tools)
{
	char	**var_name;
	char	**var_content;
	int		i;
	int		j;

	i = -1;
	j = 0;
	var_name = ft_calloc(nb_dollar + 1, sizeof(char *));
	var_content = ft_calloc(nb_dollar + 1, sizeof(char *));
	if (!var_name || !var_content)
		return (0);
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
	result = replace_name_with_content(str, var_name, var_content, nb_dollar);
	free_expanded(var_name, var_content, j);
	return (result);
}

char	*sub_dollar_in_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				if (str[i] == '$')
					str[i] = 26;
				i++;
			}
			if (str[i] == '\'' && str[i + 1])
				i++;
		}
		i++;
	}
	return (str);
}

char	*sub_back_dollar_in_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 26)
			str[i] = '$';
		i++;
	}
	return (str);
}

int	check_closed_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (EXIT_FAILURE);
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (EXIT_FAILURE);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

char	*expander(t_tools *tools, char *str)
{
	char	*result;
	int		count;

	result = NULL;
	if (check_closed_quotes(str) == 1)
		return (0);
	str = sub_dollar_in_quotes(str);
	count = count_dollar(str);
	if (count == 0)
		return (str);
	else
	{
		result = expand_str(count, result, str, tools);
		result = sub_back_dollar_in_quotes(result);
		return (result);
	}
}

char	*expander_hd(t_tools *tools, char *str)
{
	char	*result;
	int		count;

	result = NULL;
	count = count_dollar(str);
	if (count == 0)
		return (str);
	else
	{
		result = expand_str(count, result, str, tools);
		return (result);
	}
}

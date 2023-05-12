/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:34:35 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/12 23:38:48 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*replace_name_with_content(char *str, char **var_name,
		char **var_content, int count)
{
	char	*result;
	int		i;
	int		k;
	int		l;

	l = -1;
	k = 0;
	i = 0;
	if (!var_content || !var_name)
		return (str);
	result = ft_calloc(find_len_result(str, var_name, var_content, count),
		sizeof(char));
	if (!result)
		return (NULL);
	while (++l <= count)
	{
		replace_name_with_content_utils(&str, &result, &k, &i);
		if (str[k] == '$' && (ft_isalnum(str[k + 1]) || str[k + 1] == '_'
				|| str[k + 1] == '?'))
			k = k + ft_strlen(var_name[l]) + 1;
		replace_name_with_content_utils2(&var_content, &result, &l, &i);
		while (str[k] && str[k] != '$')
			result[i++] = str[k++];
	}
	return (result);
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
		return (sub_back_dollar_in_quotes(str));
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

int	check_closed_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
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
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

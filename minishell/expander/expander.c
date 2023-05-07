/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:00:57 by emuller           #+#    #+#             */
/*   Updated: 2023/05/07 17:23:46 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*find_var_env(t_tools *tools, char *var_name)
{
	int		i;
	char	*result;

	result = NULL;
	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], var_name, ft_strlen(var_name)) == 0)
			result = ft_strdup(tools->envp[i]);
		i++;
	}
	if (result)
		result = coupe_le_debut(result);
	return (result);
}

char	*find_var_name(char *str, int dollar_pos)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i])
	{
		if (i == dollar_pos && str[i + 1])
			var_name = copy_var_name(i, str);
		i++;
	}
	return (var_name);
}

int	find_len_result(char *str, char **var_name, char **var_content, int count)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (++i < count)
		len += ft_strlen(var_content[i]);
	i = -1;
	while (++i < count)
		len -= ft_strlen(var_name[i]);
	len++;
	return (len);
}

void	replace_name_with_content_utils(char **str, char **result, int *k, int *i)
{
	while ((*str)[*k] && (*str)[*k] != '$')
		(*result)[(*i)++] = (*str)[(*k)++];
	while ((*str)[*k] == '$' && (!ft_isalnum((*str)[*k + 1]) && (*str)[*k + 1] != '_'))
		(*result)[(*i)++] = (*str)[(*k)++];
	while ((*str)[*k] && (*str)[*k] != '$')
		(*result)[(*i)++] = (*str)[(*k)++];
}

void	replace_name_with_content_utils2(char ***var_content, char **result, int *l, int *i)
{
	int j;

	j = 0;
	if ((*var_content)[*l])
		while ((*var_content)[*l][j])
			(*result)[(*i)++] = (*var_content)[*l][j++];
}

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
	while (++l <= count)
	{
		replace_name_with_content_utils(&str, &result, &k, &i);
		if (str[k] == '$' && (ft_isalnum(str[k + 1]) || str[k + 1] == '_'))
			k = k + ft_strlen(var_name[l]) + 1;
		replace_name_with_content_utils2(&var_content, &result, &l, &i);
		while (str[k] && str[k] != '$')
			result[i++] = str[k++];
	}
	return (result);
}

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
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
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

char	*expander(t_tools *tools, char *str)
{
	char *result = 0;
	int count;

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
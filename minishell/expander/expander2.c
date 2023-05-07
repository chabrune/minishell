/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:26:52 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/07 17:29:05 by chabrune         ###   ########.fr       */
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

void	replace_name_with_content_utils(char **str, char **result, int *k,
		int *i)
{
	while ((*str)[*k] && (*str)[*k] != '$')
		(*result)[(*i)++] = (*str)[(*k)++];
	while ((*str)[*k] == '$' && (!ft_isalnum((*str)[*k + 1]) && (*str)[*k
			+ 1] != '_'))
		(*result)[(*i)++] = (*str)[(*k)++];
	while ((*str)[*k] && (*str)[*k] != '$')
		(*result)[(*i)++] = (*str)[(*k)++];
}

void	replace_name_with_content_utils2(char ***var_content, char **result,
		int *l, int *i)
{
	int	j;

	j = 0;
	if ((*var_content)[*l])
		while ((*var_content)[*l][j])
			(*result)[(*i)++] = (*var_content)[*l][j++];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:00:57 by emuller           #+#    #+#             */
/*   Updated: 2023/04/01 14:42:36 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char   *find_var_env(t_tools *tools, char *var_name)
{
    int i;
    char    *result = NULL;

    i = 0;
    while (tools->envp[i])
    {
        if (ft_strncmp(tools->envp[i], var_name, ft_strlen(var_name)) == 0)
            result = ft_strdup(tools->envp[i]);
		i++;
    }
	result = coupe_le_debut(result);
	return (result);
}

char *coupe_le_debut(char *env)
{
	int i;
	int j;
	int k;
	char *result;

	j = 0;
	i = 0;
	k = 0;
	if (!env)
		return(NULL);
	while(env[i++] != '=' && env[i])
		k++;
	if (env[i])
	{
		i++;
		k++;
	}
	while(env[i++])
		j++;
	i = 0;
	result = ft_calloc(sizeof(char), (j + 2));
	while(env[k])
	{
		result[i++] = env[k++];
	}
	free(env);
	return(result);
}

int		name_exist(t_tools *tools, char *str, int n)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], str, n) == 0)
            return (i);
		i++;
	}
	// et que le dernier est un =
	return (-1);
}

char	*find_var_name(t_tools *tools, char *str, int dollar_pos)
{
    int i;
	int	n;
	char *var_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && i == dollar_pos && str[i + 1])
		{
			i++;
			n = 0;
			while (name_exist(tools, str+i, n) >= 0)
				n++;
			if (tools->envp[name_exist(tools, str+i, n-1)][n-1] == '=')
			{
				var_name = ft_calloc(n + 1, sizeof(char));
				ft_strlcpy(var_name, str + i, n);
			}
			else 
				return (0);
		}
		i++;
	}
	return (var_name);
}

int		find_len_result(char *str, char **var_name, char **var_content)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	while (var_content[i])
		len += ft_strlen(var_content[i++]);
	i = 0;
	while (var_name[i])
		len -= ft_strlen(var_name[i++]);
	len++;
	printf("%d\n", len);
	return (len);
}

char	*expand_str(char *str, char **var_name, char **var_content, int count)
{
	char	*result;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	k = 0;
	l = 0;
	if(!var_content || !var_name)
		return (str);
	result = ft_calloc(find_len_result(str, var_name, var_content), sizeof(char));
	while (l < count)
	{
		while (str[k] && str[k] != '$')
			result[i++] = str[k++];
		if (str[k] == '$')
			k = k + 1 + ft_strlen(var_name[l]);
		j = 0;
		if (var_name[l])
		{
			while (var_content[l][j]);
				result[i++] = var_content[l][j++];
		}
		while (str[k] && str[k] != '$')
			result[i++] = str[k++];
		l++;
	}
	return (result);
}

int	count_dollar(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char    *expander(t_tools *tools, char *str)
{
    char *result;
	char **var_name;
	char **var_content;
	int i = 0;
	int	j = 0;
	int	count;

	count = count_dollar(str);
	if (count == 0)
		return (str);
	else
	{
		var_name  = ft_calloc(count + 1, sizeof(char *));
		var_content = ft_calloc(count + 1, sizeof(char *));
		while (str[i])
		{
			if (str[i] == '$')
			{
				var_name[j] = find_var_name(tools, str, i);
				if (var_name[j])
				{
					var_content[j] = find_var_env(tools, var_name[j]);
					j++;
				}
			}
			i++;
		}
		result = expand_str(str, var_name, var_content, count); 
		// free(var_content[j]); // il faudra free un tab
		// free(var_name[j]);// il faudra free un tab
		// free(str);
		// free(var_name);
		// free(var_content);
		return(result);
	}
}
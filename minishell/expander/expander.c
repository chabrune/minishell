/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:00:57 by emuller           #+#    #+#             */
/*   Updated: 2023/03/26 18:45:03 by emuller          ###   ########.fr       */
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
            return (1);
		i++;
	}
	// et que le dernier est un =
	return (0);
}

char	*find_var_name(t_tools *tools, char *str)
{
    int i;
	int	n;
	char *var_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			n = 0;
			while (name_exist(tools, str+i, n) == 1)
				n++;
			var_name = ft_calloc(n + 1, sizeof(char));
			ft_strlcpy(var_name, str + i, n);	
		}
		i++;
	}
	return (var_name);
}

char	*expand_str(char *str, char **var_name, char **var_content)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if(!var_content || !var_name)
		return (str);
	// Maintenant on a un tableau pour les var et les name, il faut additionner la len de tous les elements du tableau
	// et les remplacer un par un
	result = ft_calloc(ft_strlen(str) + ft_strlen(var_content) - ft_strlen(var_name) + 1, sizeof(char));
	while (str[k] && str[k] != '$')
		result[i++] = str[k++];
	if (str[k] == '$')
		k = k + 1 + ft_strlen(var_name);
	j = 0;
	while (var_content[j])
		result[i++] = var_content[j++];
	while (str[k])
		result[i++] = str[k++];
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
				// il faut faire une boucle sur tous les dollars
				var_name[j] = find_var_name(tools, str);
				var_content[j] = find_var_env(tools, var_name);
				result = expand_str(str, var_name, var_content); 
				free(var_content[j]); // il faudra free un tab
				free(var_name[j]);// il faudra free un tab
				// free(str);
				j++;
			}
			i++;
		}
		free(var_name);
		free(var_content);
		return(result);
	}
}
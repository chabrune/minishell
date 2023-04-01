/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:47:22 by emuller           #+#    #+#             */
/*   Updated: 2023/04/01 18:49:57 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
	while (env[i++] != '=' && env[i])
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
		result[i++] = env[k++];
	free(env);
	return(result);
}

int    check_var_name_exit(char *var_name, t_tools *tools)
{
    int i = 0;
    while (tools->envp[i])
    {
        if (ft_strncmp(tools->envp[i], var_name, ft_strlen(var_name)) == 0)
            return (1);
		i++;
    }   
    return (0);
}

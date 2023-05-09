/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:44:52 by emuller           #+#    #+#             */
/*   Updated: 2023/05/09 16:23:55 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab(char **tab, int j)
{
	int	k;

	k = 0;
	while (k < j)
	{
		if (tab[k])
			free(tab[k]);
		k++;
	}
	free(tab);
	return (0);
}

char	**dup_env(char **tab)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new_tab = ft_calloc(sizeof(char *), i + 1);
	if (!new_tab)
		return (0);
	i = -1;
	while (tab[++i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (free_tab(new_tab, i));
	}
	return (new_tab);
}

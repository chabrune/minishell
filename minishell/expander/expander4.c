/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:22:28 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/14 16:22:39 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == 26)
			str[i] = '$';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:49:25 by chabrune          #+#    #+#             */
/*   Updated: 2023/05/08 15:48:02 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t			i;
	unsigned char	*prem;
	unsigned char	*snd;

	prem = (unsigned char *)first;
	snd = (unsigned char *)second;
	i = 0;
	if (length == 0)
		return (0);
	if(!snd)
		return(1);
	while ((prem[i] || snd[i]) && i < length)
	{
		if (prem[i] > snd[i])
			return (1);
		else if (prem[i] < snd[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *first, const char *second)
{
	size_t			i;
	unsigned char	*prem;
	unsigned char	*snd;

	prem = (unsigned char *)first;
	snd = (unsigned char *)second;
	i = 0;
	while ((prem[i] || snd[i]))
	{
		if (prem[i] > snd[i])
			return (1);
		else if (prem[i] < snd[i])
			return (-1);
		i++;
	}
	return (0);
}

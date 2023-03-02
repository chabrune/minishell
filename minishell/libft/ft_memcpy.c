/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:48:08 by chabrune          #+#    #+#             */
/*   Updated: 2022/11/14 18:48:10 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*desti;
	char	*sourc;

	if (!dest && !src)
		return (NULL);
	i = 0;
	desti = (char *)dest;
	sourc = (char *)src;
	while (i < n)
	{
		desti[i] = sourc[i];
		i++;
	}
	return ((void *)desti);
}

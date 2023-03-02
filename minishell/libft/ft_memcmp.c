/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:47:59 by chabrune          #+#    #+#             */
/*   Updated: 2022/11/14 18:54:25 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	unsigned char	*st;
	unsigned char	*snd;

	st = (unsigned char *)pointer1;
	snd = (unsigned char *)pointer2;
	if (st == snd || size == 0)
		return (0);
	while (size--)
	{
		if (*st != *snd)
			return (*st - *snd);
		else
		{
			st++;
			snd++;
		}
	}
	return (0);
}

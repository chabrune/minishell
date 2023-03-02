/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:47:37 by chabrune          #+#    #+#             */
/*   Updated: 2022/11/15 12:09:06 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	lnb;
	int		i;

	lnb = nb;
	i = ft_len(lnb);
	str = (char *)ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	i--;
	if (lnb == 0)
		str[0] = 48;
	if (lnb < 0)
	{
		str[0] = '-';
		lnb = lnb * -1;
	}
	while (lnb > 0)
	{
		str[i] = 48 + (lnb % 10);
		lnb = lnb / 10;
		i--;
	}
	return (str);
}
